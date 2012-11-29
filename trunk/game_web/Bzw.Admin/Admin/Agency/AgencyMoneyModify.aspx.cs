using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using BCST.Common;
using Bzw.Data;
using UiCommon;

public partial class Admin_Agency_UserManager_AgencyMoneyModify : AdminBasePage
{
	protected DataRow AgencyInfo;

	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "20" );

		string name = CommonManager.Web.Request( "agencyName", "" );
		if( string.IsNullOrEmpty( name ) )
		{
			CommonManager.Web.RegJs( this, "history.back();", true );
			return;
		}

		AgencyInfo = Agency.Default.GetInfo( name );

		if( AgencyInfo == null )
		{
			CommonManager.Web.ResponseEnd( "AgencyView.aspx", true );
		}

		//if( !IsPostBack )
		//{
		//    tbxAccount.Text = UiCommon.StringConfig.MoneyChu100( AgencyInfo["Account"] );
		//}

		DataSet ds = DbSession.Default.FromProc( "Web_pGetDataPager" )
			.AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
			.AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
			.AddInputParameter( "@Columns", DbType.String, "*" )
			.AddInputParameter( "@TableName", DbType.String, "Web_vAgencyAccountLog" )
			.AddInputParameter( "@Wheres", DbType.String, " and AgencyID=" + AgencyInfo["AgencyID"].ToString() )
			.AddInputParameter( "@KeyName", DbType.String, "ID" )
			.AddInputParameter( "@OrderBy", DbType.String, "ID desc" )
			.ToDataSet();

		if( ds.Tables.Count > 0 )
		{
			anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
			anpPageIndex.CurrentPageIndex = PageIndex;

			if( ds.Tables[1].Rows.Count > 0 )
			{
				ltNonData.Visible = false;
				rptDataList.Visible = true;
				rptDataList.DataSource = ds.Tables[1];
				rptDataList.DataBind();
			}
			else
			{
				ltNonData.Visible = true;
				rptDataList.Visible = false;
			}
		}
	}

	protected void btnModfyMoney_Click( object sender, EventArgs e )
	{
		if( !CommonManager.Web.CheckPostSource() )
			return;
		if( !IsValid )
			return;

		if( AgencyInfo == null )
			return;

		long old_account = (long)AgencyInfo["Account"];

		if (!CommonManager.String.IsInteger(tbxAccount.Text.Trim()))
		{
			CommonManager.Web.RegJs(this, "alert('输入的金币数必须为数字！');location.href=location.href;", false);
			return;
		}
		if (Convert.ToInt64(tbxAccount.Text.Trim()) < 0)
		{
			CommonManager.Web.RegJs(this, "alert('输入的金币数必须为大于0的数字！');location.href=location.href;", false);
			return;
		}
		long new_account = string.IsNullOrEmpty( tbxAccount.Text.Trim() ) ? 0L : long.Parse( UiCommon.StringConfig.MoneyCheng100( tbxAccount.Text.Trim() ) );

		long range = new_account - old_account;

		if( range != 0 )
		{
			using( DbTrans trans = DbSession.Default.BeginTrans() )
			{
				try
				{
					trans.FromSql( "update Web_Agency set Account=@Account Where AgencyID=@AgencyID" )
						.AddInputParameter( "@Account", DbType.Int64, new_account )
						.AddInputParameter( "@AgencyID", DbType.Int32, AgencyInfo["AgencyID"] )
						.Execute();

					//记录日志
					string sql = "insert into Web_AgencyAccountLog (AdminID,AgencyID,MoneyB,Range,MoneyA,InputDate) values (@AdminID,@AgencyID,@MoneyB,@Range,@MoneyA,getdate()); ";
                    sql += " exec Web_pAgencyMoneyChangeLogAdd @AgencyID,'',@MoneyB,@Range,@MoneyA," + (int)BLL.AgencyMoneyLog.LogType.管理员改金币 + @",'" + BLL.AgencyMoneyLog.LogType.管理员改金币.ToString() + @"','操作人" + AdminUserName + "(后台管理员)'";

					trans.FromSql( sql )
						.AddInputParameter( "@AdminID", DbType.Int32, AdminUserID )
						.AddInputParameter( "@AgencyID", DbType.Int32, AgencyInfo["AgencyID"] )
						.AddInputParameter( "@MoneyB", DbType.Int64, old_account )
						.AddInputParameter( "@Range", DbType.Int64, range )
						.AddInputParameter( "@MoneyA", DbType.Int64, new_account )
						.Execute();

					trans.Commit();

					//new BLL.AdminLog().Add( UiCommon.AdminLoginInfo.UserName, "修改了代理[" + AgencyInfo["AgencyName"].ToString() + "]的金币为" + UiCommon.StringConfig.MoneyChu100( new_account ) + "，变动幅度为" + UiCommon.StringConfig.MoneyChu100( range ) );

					CommonManager.Web.RegJs( this, "alert('修改成功！');location.href='" + Utility.Common.UrlValue + "';", false );
				}
				catch( Exception ex )
				{
					trans.Rollback();
					CommonManager.Web.RegJs( this, "alert('修改失败！错误原因：" + Server.HtmlEncode( ex.Message ) + "');", false );
					return;
				}
			}
			return;
		}
		CommonManager.Web.RegJs( this, "alert('修改成功！');location.href='" + Utility.Common.UrlValue + "';", false );
	}
}
