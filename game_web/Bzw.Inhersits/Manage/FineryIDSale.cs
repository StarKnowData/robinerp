using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using BCST.Common;
using System.Text.RegularExpressions;
using Utility;
using Bzw.Data;
using System.Data;

namespace Bzw.Inhersits.Manage
{
	public partial class FineryIDSale : UiCommon.ManageBasePage
	{
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
		/// frmLogin 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.HtmlControls.HtmlForm frmLogin;

		/// <summary>
		/// fineryLB 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.Label fineryLB;

		/// <summary>
		/// priceLB 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.Label priceLB;

		/// <summary>
		/// explainLB 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.Label explainLB;

		/// <summary>
		/// Panel1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.Panel Panel1;

		/// <summary>
		/// webfooter1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.UserControl webfooter1;
		public string fineryid = CommonManager.Web.Request( "id", "" );
		protected void Page_Load( object sender, EventArgs e )
		{
			if( !Common.IsNumber( fineryid ) )
			{
				Utility.Common.OutMsgBox( "非法操作", "" );
			}
			string sql = "select * from Web_FineryID where FineryID='" + fineryid + "'";
			DataTable tb = DbSession.Default.FromSql( sql ).ToDataTable();
			if( tb.Rows.Count > 0 )
			{
				DataRow row = tb.Rows[0];
				this.fineryLB.Text = row["FineryID"].ToString();
				this.priceLB.Text = UiCommon.StringConfig.AddZeros(row["Price"].ToString());
				this.explainLB.Text = row["Explain"].ToString();
			}
		}

		protected void Button1_Click( object sender, EventArgs e )
		{
			string userid = UiCommon.UserLoginInfo.UserID;
			string pwd = Utility.Common.md5( Common.FilterString( Common.GetStringOfForm( "pwd" ) ) );
			Dictionary<string, object> dic = new Dictionary<string, object>();
			DbSession.Default.FromProc( "Web_pBuyFineryID" )
				.AddInputParameter( "@UserID", DbType.Int32, userid )
				.AddInputParameter( "@FineryID", DbType.Int32, fineryid )
				.AddInputParameter( "@PassWord", DbType.Single, pwd )
				.AddReturnValueParameter( "@ReturnValue", DbType.Int32 )
				.Execute( out dic );
			int re = (int)dic["ReturnValue"];
			if( re == -2 )
			{
				CommonManager.Web.RegJs( this, "alert('购买前请提出游戏')", false );
				return;
			}
			if( re == -1 )
			{
                CommonManager.Web.RegJs(this, "alert('您银行的" + UiCommon.StringConfig.MoneyName + "数不足购买此靓号')", false);
				this.Panel1.Visible = true;
				return;
			}
			if( re == 0 )
			{
				Utility.Common.OutMsgBox( "很抱歉！靓号已售出，请挑选其他靓号", "" );
				return;
			}
			if( re == 1 )
			{
				Utility.Common.OutMsgBox( "恭喜您！购买成功，请到管理中心激活，靓号需激活后才能登陆游戏", "/Manage/FineryIDManage.aspx" );
				return;
			}
		}
	}
}
