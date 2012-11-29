using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using BCST.Common;
using Bzw.Data;
using System.Data;
using Utility;

namespace Bzw.Inhersits.Manage
{
	public partial class FineryIDDataCopy : UiCommon.ManageBasePage
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
		/// frmcopy 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.HtmlControls.HtmlForm frmcopy;

		/// <summary>
		/// hidden 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.TextBox hidden;

		/// <summary>
		/// submit 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.HtmlControls.HtmlInputSubmit submit;

		/// <summary>
		/// webfooter1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.UserControl webfooter1;
		public string userid = UiCommon.UserLoginInfo.UserID;
		public string username = UiCommon.UserLoginInfo.UserName;
		public string fineryid = CommonManager.Web.Request( "id", "" );
		public string frusername = string.Empty;
		protected void Page_Load( object sender, EventArgs e )
		{
			if( string.IsNullOrEmpty( fineryid ) || fineryid == "" )
			{
				Utility.Common.OutMsgBox( "非法操作", "/Manage/FineryID.aspx" );
			}
			FineryBind();
		}

		//根据靓号ID查询用户名，以及判断靓号ID是否被激活
		public void FineryBind()
		{
			string sqltext = "select UserName from TUsers where UserID='" + fineryid + "'";
			DataTable tb = DbSession.Default.FromSql( sqltext ).ToDataTable();
			if( tb.Rows.Count > 0 )
			{
				DataRow row = tb.Rows[0];
				frusername = row["UserName"].ToString();
			}
			else
			{
				Utility.Common.OutMsgBox( "很抱歉！靓号未激活，请您先激活再使用数据转移功能", "/Manage/FineryIDManage.aspx" );
				return;
			}
		}

		//数据转移
		protected void Button1_Click( object sender, EventArgs e )
		{
			string password = Utility.Common.md5( Common.FilterString( Common.GetStringOfForm( "pwd" ) ) );
			Dictionary<string, object> dic = new Dictionary<string, object>();
			DbSession.Default.FromProc( "Web_pFineryIDCopyData" )
				.AddInputParameter( "@UserID", DbType.Int32, userid )
				.AddInputParameter( "@FineryID", DbType.Int32, fineryid )
				.AddInputParameter( "@PassWordInput", DbType.Single, password )
				.AddReturnValueParameter( "@ReturnValue", DbType.Int32 )
				.Execute( out dic );
			int re = (int)dic["ReturnValue"];
			if( re == -1 )
			{
				CommonManager.Web.RegJs( this, "alert('很抱歉！该靓号已经使用过数据转移，如需再次转移请重新购买靓号');", false );
			}
			if( re == -2 )
			{
				CommonManager.Web.RegJs( this, "alert('很抱歉！您输入的密码有误，请重新输入您大号密码')", false );
			}
			if( re == -3 )
			{
				CommonManager.Web.RegJs( this, "alert('很抱歉！转移数据时大号需退出大厅')", false );
			}
			if( re == -4 )
			{
				CommonManager.Web.RegJs( this, "alert('很抱歉！转移数据时靓号号需退出大厅')", false );
			}
			if( re == 0 )
			{
				CommonManager.Web.RegJs( this, "alert('很抱歉！服务器繁忙，请稍后再试')", false );
			}
			if( re == 1 )
			{
				//CommonManager.Web.RegJs( this, "alert('恭喜您！数据转移成功')", false );
				Utility.Common.OutMsgBox( "恭喜您！数据转移成功，您大号的数据已全部转至新靓号中，祝你游戏愉快", "/Manage/FineryIDManage.aspx" );
			}
		}

	}
}
