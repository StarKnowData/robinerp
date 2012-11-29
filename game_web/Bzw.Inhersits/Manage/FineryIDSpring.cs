using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using Bzw.Data;
using Utility;
using BCST.Common;

namespace Bzw.Inhersits.Manage
{
	public partial class FineryIDSpring : UiCommon.ManageBasePage
	{
		/// <summary>
		/// Head1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.HtmlControls.HtmlHead Head1;

		/// <summary>
		/// frmLogin 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.HtmlControls.HtmlForm frmLogin;

		/// <summary>
		/// Control1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.UserControl Control1;

		/// <summary>
		/// Control2 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.UserControl Control2;

		/// <summary>
		/// Left1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.UserControl Left1;

		/// <summary>
		/// btnSubmit 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.HtmlControls.HtmlInputSubmit btnSubmit;

		/// <summary>
		/// webfooter1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.UserControl webfooter1;
		public string userid = UiCommon.UserLoginInfo.UserID;
		public string fineryid = CommonManager.Web.Request( "id", "" );
		protected void Page_Load( object sender, EventArgs e )
		{
			if( string.IsNullOrEmpty( fineryid ) || fineryid == "" )
			{
				Utility.Common.OutMsgBox( "非法操作", "/Manage/FineryID.aspx" );
			}
		}

		protected void Button1_Click( object sender, EventArgs e )
		{
			string username = Common.FilterString( Common.GetStringOfForm( "username" ) );
			string nickname = Server.HtmlEncode( Common.GetStringOfForm( "nickname" ).Replace( "'", "''" ) );
			string password = Utility.Common.md5( Common.FilterString( Common.GetStringOfForm( "pwd" ) ) );
			string RegisterIP = Common.RequestIP;
			Dictionary<string, object> dic = new Dictionary<string, object>();
			DbSession.Default.FromProc( "Web_pUsersAddByFineryID" )
				.AddInputParameter( "@UserID", DbType.Int32, userid )
				.AddInputParameter( "@FineryID", DbType.Int32, fineryid )
				.AddInputParameter( "@PassWordInput", DbType.String, password )
				.AddInputParameter( "@UserName", DbType.String, username )
				.AddInputParameter( "@NickName", DbType.String, nickname )
				.AddInputParameter( "@RegisterIP", DbType.String, RegisterIP )
				.AddReturnValueParameter( "@ReturnValue", DbType.Int32 )
				.Execute( out dic );
			int re = (int)dic["ReturnValue"];
			if( re == -1 )
			{
				CommonManager.Web.RegJs( this, "alert('很抱歉！用户名已存在')", false );
				return;
			}
			if( re == -2 )
			{
				CommonManager.Web.RegJs( this, "alert(很抱歉！昵称已存在)", false );
				return;
			}
			if( re == -3 )
			{
				CommonManager.Web.RegJs( this, "alert('很抱歉！您输入的靓号密码有误，请您核实后再激活')", false );
				return;
			}
			if( re == -4 )
			{
				Utility.Common.OutMsgBox( "很抱歉！已被激活的靓号，不能重复激活", "/Manage/FineryIDManage.aspx" );
				return;
			}
			if( re == -5 )
			{
				Utility.Common.OutMsgBox( "很抱歉！此靓号可能已被激活，不能重复激活", "/Manage/FineryIDManage.aspx" );
				return;
			}
			if( re == 0 )
			{
				CommonManager.Web.RegJs( this, "alert('很抱歉！激活失败，可能服务器忙')", false );
				return;
			}
			if( re == 1 )
			{
				Utility.Common.OutMsgBox( "恭喜您！激活成功，你可以用此号正常游戏及使用数据转移功能了，\\n登录密码，银行密码为您的靓号密码，基本信息与您大号保持一至", "/Manage/FineryIDManage.aspx" );
				return;
			}
		}
	}
}
