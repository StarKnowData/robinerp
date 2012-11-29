using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Bzw.Data;
using System.Data;
using BCST.Common;

namespace Bzw.Web.Admin.SConfig
{
	public partial class BankAccessLog : AdminBasePage
	{
		protected int IndexPage
		{
			get
			{
				string tmp = CommonManager.Web.Request("page","");
				if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
				{
					return 1;
				}
				return int.Parse(tmp);
			}
		}
		public int number = 0;
		public string sbWhere=string.Empty;
		protected void Page_Load( object sender, EventArgs e )
		{
			AdminPopedom.IsHoldModel("09");
			delete();
			string username = CommonManager.Web.Request("username","");
			string type = CommonManager.Web.Request("type","");
			if(!string.IsNullOrEmpty(username))
			{
				if( type == "1" )
				{
					sbWhere += " and NickName like '%" + username + "%'";
				}
				else
				{
					sbWhere += " and UserName like '%" + username + "%'";
				}

			}
			DataSet ds=DbSession.Default.FromProc("Web_pGetDataPager")
				.AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
				.AddInputParameter( "@CurrentPage", DbType.Int32, IndexPage )
				.AddInputParameter( "@Columns", DbType.String, "*" )
				.AddInputParameter( "@TableName", DbType.String, "Web_vMoneyChangeRecord" )
				.AddInputParameter( "@Wheres", DbType.String, sbWhere.ToString() )
				.AddInputParameter( "@KeyName", DbType.String, "ID" )
				.AddInputParameter( "@OrderBy", DbType.String, "TimeEx desc" )
				.ToDataSet();
			if( ds.Tables.Count > 0 )
			{
				anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
				anpPageIndex.CurrentPageIndex = IndexPage;
				if( ds.Tables[1].Rows.Count > 0 )
				{
					rptDataList.Visible = true;
					ltNonData.Visible = false;
					rptDataList.DataSource = ds.Tables[1];
					rptDataList.DataBind();
				}
				else
				{
					rptDataList.Visible = false;
					ltNonData.Visible = true;
				}
			}
		}

		public void delete()
		{
			string act = CommonManager.Web.Request( "action", "" );
			if( act == "del" )
			{
				string id = CommonManager.Web.Request( "id", "" );
				string adminName = AdminInfo["UserName"].ToString();
				string system = Utility.Common.GetOS;
				string descript = "删除了1条用户存取记录";
				string sqltext = "delete TMoneyChangeRecord where ID=" + id + "";
				DbSession.Default.FromSql( sqltext ).Execute();
				new BLL.Member().InsertAdminModifyLog( adminName, Utility.Common.RequestIP, system, descript, 1 );
				CommonManager.Web.RegJs( this, "alert('删除成功');RefreshMeDelParam('action=del&');", false );
			}
		}
	}
}
