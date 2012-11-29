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
using System.Data.SqlClient;
using BCST.Common;

public partial class Admin_Agency_ChildAgencyDetail : AdminBasePage
{
	protected DataRow info;

    protected void Page_Load(object sender, EventArgs e)
	{
        AdminPopedom.IsHoldModel("17");

		string agencyname = CommonManager.Web.RequestUrlDecode( "agencyName", "" );
		if( string.IsNullOrEmpty( agencyname ) )
			return;

		info = Agency.Default.GetInfo(agencyname);
		if( info == null )
		{
			CommonManager.Web.RegJs(this,"alert('参数错误！');history.back();",false);
		}
    }
}
