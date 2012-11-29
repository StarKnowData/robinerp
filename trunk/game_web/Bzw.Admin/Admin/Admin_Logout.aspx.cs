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
using BCST.Cache;
using UiCommon;
using BCST.Common;

public partial class Admin_Logout : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
		object tmp = BCSTCache.Default.Get<SessionCache>(StringConfig.AdminCacheName);
		if (tmp != null)
			BCSTCache.Default.Delete<SessionCache>(StringConfig.AdminCacheName);
		tmp = BCSTCache.Default.Get<CookiesCache>(StringConfig.AdminCacheName);
		if (tmp != null)
			BCSTCache.Default.Delete<CookiesCache>(StringConfig.AdminCacheName); 
		
		//BCSTCache.Default.Delete<SessionCache>( StringConfig.AdminCacheName );
		//BCSTCache.Default.Delete<CookiesCache>( StringConfig.AdminCacheName );
		CommonManager.Web.ResponseEnd( "Default.aspx", true );
    }
}
