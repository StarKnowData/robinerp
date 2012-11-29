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


public partial class Admin_Users_LoginIp_seach : AdminBasePage
{
	public string beginTime, EndTime;
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "04" );
		DateTime dt = DateTime.Now;
		beginTime = dt.AddDays( -1 ).ToString( "yyyy-MM-dd" );
		EndTime = Convert.ToDateTime( DateTime.Now.ToString() ).ToString( "yyyy-MM-dd" );

	}
}
