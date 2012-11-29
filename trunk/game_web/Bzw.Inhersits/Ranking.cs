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
	public partial class Ranking : UiCommon.BasePage
	{
		/// <summary>
		/// Head1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.HtmlControls.HtmlHead Head1;

		protected void Page_Load( object sender, EventArgs e )
		{
			string id = Utility.Common.SqlEncode( Utility.Common.GetStringOfUrl( "id" ) );
			if( string.IsNullOrEmpty( id ) || !BCST.Common.CommonManager.String.IsInteger( id ) )
			{
				Response.Redirect( "/RankMoney.aspx" );
			}
			else
			{
				//静态页面过期常量的KEY
				string Key_Default_Build = "Key_RankGamePoint_Build";
				//动态页面Url
				string dongPageUrl = "/Ranking2.aspx?id=" + id + "&name=" + Server.UrlEncode( Utility.Common.GetStringOfUrl( "name" ) );
				//静态页面Url
				string jingPageUrl = "/RankGamePoint_" + id + ".html";
				//静态文件存放根目录
				string RootFilePath = "/Html/Ranking";

				string returnPageUrl = new UiCommon.BuildStatic().PageBuild( Key_Default_Build, dongPageUrl, jingPageUrl, RootFilePath );
				Response.Redirect( returnPageUrl );
			}
		}

	}

}
