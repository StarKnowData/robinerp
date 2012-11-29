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
using Utility;
using BCST.Common;
using Bzw.Data;

public partial class Admin_Prizes_PrizesEdit : AdminBasePage
{
	string PrizesID;
	public string Award_Name = "", leitype = "", Award_MoneyCost = "", Award_OnLineTime = "", Award_Num = "", picture = "", Award_hot = "";
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "11" );

		string tmp = CommonManager.Web.Request( "id", "" );
		if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
		{
			Alert( "请勿非法操作！", null );
			return;
		}
		else
			PrizesID = tmp;//Limit.editCharacter(Limit.getFormValue("id"));
		DataTable sd = new DataTable();
		string sql = "select * from Web_Award where Award_id=" + PrizesID + "";
		sd = DbSession.Default.FromSql( sql ).ToDataTable(); //sqlconn.sqlReader(sql);
		if( sd.Rows.Count > 0 && !IsPostBack )
		{
			string action = CommonManager.Web.Request( "action", "" );
			if( !string.IsNullOrEmpty( action ) && action == "delimg" )
			{
				//删除图片
				CommonManager.File.DeleteFile( sd.Rows[0]["Award_pic"].ToString() );
				DbSession.Default.FromSql( "update Web_Award set Award_pic='' where Award_id=" + tmp ).Execute();
				CommonManager.Web.RegJs( this, @"RefreshMeDelParam('[?&]?action=delimg');", false );
				return;
			}

			Award_Name = sd.Rows[0]["Award_Name"].ToString();
			leitype = sd.Rows[0]["Award_type"].ToString();
			Award_MoneyCost = sd.Rows[0]["Award_MoneyCost"].ToString();
			Award_OnLineTime = sd.Rows[0]["Award_OnLineTime"].ToString();
			Award_Num = sd.Rows[0]["Award_Num"].ToString();
			//picture = sd.Rows[0]["Award_pic"].ToString();
			Award_Info.Value = sd.Rows[0]["Award_Info"].ToString();
			Award_hot = sd.Rows[0]["Award_hot"].ToString();

			if( !string.IsNullOrEmpty( sd.Rows[0]["Award_pic"].ToString() ) && sd.Rows[0]["Award_pic"].ToString().ToLower() != "/upload/prizes/nopic.jpg" )
			{
				phFileImage.Visible = false;
				phImageUrl.Visible = true;
				txtImageUrl.Text = sd.Rows[0]["Award_pic"].ToString();
			}
			else
			{
				phImageUrl.Visible = false;
				phFileImage.Visible = true;
			}

		}
		sd.Clear();
	}

	protected void Prizes_Edit( object sender, EventArgs e )
	{
		string sqlAward_Name, sqlleitype, sqlAward_MoneyCost, sqlAward_OnLineTime, sqlAward_Num, sqlpicture, sqlAward_Info, sqlAward_hot;

		sqlAward_Name = CommonManager.Web.RequestForm( "Award_Name", "" );
		if( sqlAward_Name.ToString() == "" )
		{
			Alert( "温馨提示：\\n\\n奖品名称不能为空！", null );
			return;
		}
		sqlleitype = CommonManager.Web.RequestForm( "leitype", "" );
		sqlAward_MoneyCost = CommonManager.Web.RequestForm( "Award_MoneyCost", "" );
		if (!CommonManager.String.IsInteger(sqlAward_MoneyCost) || Convert.ToInt32(sqlAward_MoneyCost) < 0)
		{
			CommonManager.Web.RegJs(this, "alert('[奖品所需"+UiCommon.StringConfig.GoldName+"数]必须为不小于0的数字！');location.href=location.href;", false);
			return;
		}
		sqlAward_OnLineTime = CommonManager.Web.RequestForm( "Award_OnLineTime", "" );
		if (!CommonManager.String.IsInteger(sqlAward_OnLineTime) || Convert.ToInt32(sqlAward_OnLineTime) < 0)
		{
			CommonManager.Web.RegJs(this, "alert('[奖品所需游戏时长数]必须为不小于0的数字！');location.href=location.href;", false);
			return;
		}
		sqlAward_Num = CommonManager.Web.RequestForm( "Award_Num", "" );//Limit.editCharacter( Limit.getFormValue( "Award_Num" ) );
		if (!CommonManager.String.IsInteger(sqlAward_Num) || Convert.ToInt32(sqlAward_Num) < 0)
		{
			CommonManager.Web.RegJs(this, "alert('[奖品数量]必须为不小于0的数字！');location.href=location.href;", false);
			return;
		}
		//sqlpicture = CommonManager.Web.RequestForm( "picture", "" );
		sqlAward_Info = Award_Info.Value; //CommonManager.Web.RequestForm( "Award_Info", "" );
		sqlAward_hot = CommonManager.Web.RequestForm( "Award_hot", "" );


		//上传图片
		if( fuImage.HasFile )
		{
			try
			{
				if( !CommonManager.File.UploadFile( fuImage.PostedFile, 300 * 1024, new string[] { "jpg", "jpeg", "gif" }, "/Upload/Prizes", FileOperator.RenameType.当前时间及随机数字, out sqlpicture ) )
				{
					sqlpicture = "";
				}
			}
			catch( Exception ex )
			{
				//Response.Write( "文件上传错误：" + ex.Message + "<a href='javascript:history.back();'>点此返回上一页</a>" );
				CommonManager.Web.RegJs(this, "alert('文件上传错误：" + ex.Message + "');location.href=location.href;", false);
				return;
			}
		}
		else
		{
			sqlpicture = txtImageUrl.Text.Trim();
		}

		string sql = @"UPDATE [Web_Award] SET 
	[Award_Name] = @Award_Name,[Award_Info] = @Award_Info,[Award_Pic] = @Award_Pic,[Award_Num] = @Award_Num,[Award_MoneyCost] = @Award_MoneyCost,[Award_Type] = @Award_Type,[Award_Hot] = @Award_Hot,[Award_OnLineTime] = @Award_OnLineTime
	WHERE Award_ID=@Award_ID ";

		int SqlState = DbSession.Default.FromSql( sql )
			.AddInputParameter( "@Award_Name", DbType.String, sqlAward_Name )
			.AddInputParameter( "@Award_Info", DbType.String, sqlAward_Info )
			.AddInputParameter( "@Award_Pic", DbType.String, sqlpicture )
			.AddInputParameter( "@Award_Num", DbType.String, sqlAward_Num )
			.AddInputParameter( "@Award_MoneyCost", DbType.String, sqlAward_MoneyCost )
			.AddInputParameter( "@Award_Type", DbType.String, sqlleitype )
			.AddInputParameter( "@Award_Hot", DbType.String, sqlAward_hot )
			.AddInputParameter( "@Award_OnLineTime", DbType.String, sqlAward_OnLineTime )
			.AddInputParameter( "@Award_ID", DbType.String, PrizesID )
			.Execute();

		string adminName = AdminInfo["UserName"].ToString();
		string descript = "修改奖品资料！奖品名称：" + sqlAward_Name;
		string system = Common.GetOS;
		if( SqlState >= 0 )
		{
			new BLL.Member().InsertAdminModifyLog( adminName, Common.RequestIP, system, descript, 1 );
			Alert( "温馨提示：\\n\\n奖品资料修改成功！", "Prizes.aspx" );
		}
		else
		{
			new BLL.Member().InsertAdminModifyLog( adminName, Common.RequestIP, system, descript, 0 );
			Alert( "温馨提示：\\n\\n奖品资料修改失败！", null );
		}		
	}
}
