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

using UiCommon;
using Utility;


namespace Bzw.Inhersits
{
	public partial class UserLogin : UiCommon.AppBasePage
	{

		protected void Page_Load( object sender, EventArgs e )
		{
			string url = Common.GetStringOfUrl( "url" );

			//string comString = StringConfig.WebSiteName.ToLower() + "/app";
			// if (url.ToLower().IndexOf(comString) != -1)
			//{
			string errPage = "/app/ErrPage.aspx";

			string userid = Common.SqlEncode( Common.GetStringOfUrl( "userid" ) );
			string SnToken = Common.SqlEncode( Common.GetStringOfUrl( "Token" ) );

			//Response.Write(userid + "<br />" + SnToken + "<br />" + url);
			//Response.End();

			if( !Common.IsNumber( userid ) || SnToken.Length == 0 )
			{
				Response.Redirect( errPage, true );
			}

			//判断是否已登录
			if( UiCommon.UserLoginInfo.IsLogin && UiCommon.UserLoginInfo.UserID.Trim().ToLower() == userid.Trim().ToLower() )
			{
				Response.Redirect( url, true );
			}

			BLL.Member member = new BLL.Member();
			string dbUserName = member.GetNameByUserID( userid, SnToken );
			if( dbUserName == null || dbUserName.Length == 0 )
			{
				Response.Redirect( errPage, true );
			}
			else
			{
				//更新用户的登录次数、最后登录IP、最后登录时间
				member.UpdateLastLogin( dbUserName, Utility.Common.RequestIP );

				UserLoginInfo.SetInfo( userid, dbUserName );

				string f = "?";
				if( url.IndexOf( "?" ) >= 0 )
					f = "&";

				url = url + f;
				Response.Redirect( url, true );
			}
			//}
			//else
			//{
			//    Response.Redirect(url);
			//}

		}
	}
}
