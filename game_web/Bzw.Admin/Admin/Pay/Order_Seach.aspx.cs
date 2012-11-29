using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using Bzw.Data;
using BCST.Common;

namespace Bzw.Web.Admin.Pay
{
	public partial class Order_Seach : AdminBasePage
	{
		
		public string where = string.Empty;
		public int number = 0;
		protected void Page_Load( object sender, EventArgs e )
		{
			AdminPopedom.IsHoldModel( "04" );
			string orderid = CommonManager.Web.Request("order","");
			if(!string.IsNullOrEmpty( orderid ))
			{
				where += " and orderID like '%" + orderid + "%'";
				DataSet ds = DbSession.Default.FromProc( "Web_pGetDataPager" )
				.AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
				.AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
				.AddInputParameter( "@Columns", DbType.String, "*" )
				.AddInputParameter( "@TableName", DbType.String, "Web_RMBCost" )
				.AddInputParameter( "@Wheres", DbType.String, where )
				.AddInputParameter( "@KeyName", DbType.String, "PayID" )
				.AddInputParameter( "@OrderBy", DbType.String, "PayID desc" )
				.ToDataSet();

				if( ds.Tables.Count > 0 )
				{
					anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
					anpPageIndex.CurrentPageIndex = PageIndex;

					if( ds.Tables[1].Rows.Count > 0 )
					{
						rptDataList.Visible = true;
						rptDataList.DataSource = ds.Tables[1];
						rptDataList.DataBind();
						ltNonData.Visible = false;
					}
					else
					{
						ltNonData.Visible = true;
						rptDataList.Visible = false;
					}
				}
			}

		}
	}
}
