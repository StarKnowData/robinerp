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

namespace Bzw.Inhersits
{
    public partial class Down : UiCommon.BasePage
	{
		protected void Page_Load( object sender, EventArgs e )
		{
			//静态页面过期常量的KEY
			string Key_Default_Build = "Key_Down_Build";
			//动态页面Url
			string dongPageUrl = "/Down2.aspx";
			//静态页面Url
			string jingPageUrl = "/Down.html";
			//静态文件存放根目录
			string RootFilePath = "/Html";

			string returnPageUrl = new UiCommon.BuildStatic().PageBuild( Key_Default_Build, dongPageUrl, jingPageUrl, RootFilePath );
			Response.Redirect( returnPageUrl );
		}
	}
}
