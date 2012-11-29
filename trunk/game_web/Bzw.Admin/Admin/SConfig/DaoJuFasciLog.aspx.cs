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
using System.Text;
using Bzw.Data;
public partial class Admin_SConfig_DaoJuFasciLog : AdminBasePage
{
	
    public string GaoJiPropFasci = string.Empty;
    public string ZhongJiPropFasci = string.Empty;
    public string DiJiPropFasci = string.Empty;
	protected void Page_Load( object sender, EventArgs e )
	{	
		AdminPopedom.IsHoldModel( "15" );

		StringBuilder where = new StringBuilder( );
        string userName = string.Empty;
		string un = CommonManager.Web.RequestUrlDecode( "un", "" );
        if (!string.IsNullOrEmpty(un))
        {
            userName = un;
            where.Append(" and UserName='" + un + "'");
        }
        where.Append(" and ID<>0");			

		DataSet ds = DbSession.Default.FromProc( "Web_pGetDataPager" )
			.AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
			.AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
			.AddInputParameter( "@Columns", DbType.String, "*" )
			.AddInputParameter( "@TableName", DbType.String, "Web_VFasciClearPropLog" )
			.AddInputParameter( "@Wheres", DbType.String, where.ToString() )
			.AddInputParameter( "@KeyName", DbType.String, "ID" )
			.AddInputParameter( "@OrderBy", DbType.String, "InputDate desc,ID desc" )
			.ToDataSet();

		if( ds.Tables.Count > 0 )
		{
			anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
			anpPageIndex.CurrentPageIndex = PageIndex;

			if( ds.Tables[1].Rows.Count > 0 )
			{
				rptDataList.Visible = true;
				lbNonData.Visible = false;
				rptDataList.DataSource = ds.Tables[1];
				rptDataList.DataBind();
			}
			else
			{
				rptDataList.Visible = false;
				lbNonData.Visible = true;
			}
		}

        DataRow dr = new BLL.Member().GetPropFasciStatLog(userName);
        if (dr != null)
        {
            GaoJiPropFasci = dr["GaoJi"].ToString();
            ZhongJiPropFasci = dr["ZhongJi"].ToString();
            DiJiPropFasci = dr["DiJi"].ToString();
        }
		
	}

}
