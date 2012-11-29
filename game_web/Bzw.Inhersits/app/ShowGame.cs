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
	public partial class ShowGame : UiCommon.AppBasePage
	{
		protected void Page_Load( object sender, EventArgs e )
		{
			string id = Utility.Common.SqlEncode( Utility.Common.GetStringOfUrl( "id" ) );
			if( string.IsNullOrEmpty( id ) || !BCST.Common.CommonManager.String.IsInteger( id ) )
			{
				Response.Write( "请勿非法访问！" );
				Response.End();
				return;
			}
			else
			{
				//静态页面过期常量的KEY
				string Key_Default_Build = "Key_GameRule_Build";
				//动态页面Url
				string dongPageUrl = "/app/ShowGameHtml.aspx?id=" + id;
				//静态页面Url
				string jingPageUrl = "/GameInfo_Client_" + id + ".html";
				//静态文件存放根目录
				string RootFilePath = "/Html/GameInfo";

				string returnPageUrl = new UiCommon.BuildStatic().PageBuild( Key_Default_Build, dongPageUrl, jingPageUrl, RootFilePath );
				Response.Redirect( returnPageUrl );
			}


			/*
			if (Request["id"] != null)
			{

				string nameID = Request["id"].ToString();
				if (!BCST.Common.CommonManager.String.IsInteger(nameID))
				{
					Response.Write("参数调用出错!");
					Response.End();
				}

				////转到生成静态页面
				//Response.Redirect("/Html/GameInfo/" + nameID + ".html");

				Response.Redirect("/app/ShowGameHtml.aspx?id=" + nameID);
			}*/

		}
	}
}
