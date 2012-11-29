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
using Bzw.WebLibrary;

namespace Bzw.Inhersits
{
    public partial class GameInfo : UiCommon.BasePage
	{
		protected void Page_Load( object sender, EventArgs e )
		{
            SeoSetting(SeoConfig.Config.DefaultSeo);
			string id = Utility.Common.SqlEncode( Utility.Common.GetStringOfUrl( "id" ) );
			if( string.IsNullOrEmpty( id ) || !BCST.Common.CommonManager.String.IsInteger( id ) )
			{
				Response.Write( "<script>history.back();</script>" );
				Response.End();
				return;
			}
			else
			{
				//静态页面过期常量的KEY
				string Key_Default_Build = "Key_GameRule_Build";
				//动态页面Url
				string dongPageUrl = "/GameInfo3.aspx?id=" + id;
				//静态页面Url
				string jingPageUrl = "/GameInfo_" + id + ".html";
				//静态文件存放根目录
				string RootFilePath = "/Html/GameInfo";

				string returnPageUrl = new UiCommon.BuildStatic().PageBuild( Key_Default_Build, dongPageUrl, jingPageUrl, RootFilePath );
				Response.Redirect( returnPageUrl );
			}
		}
	}

}
