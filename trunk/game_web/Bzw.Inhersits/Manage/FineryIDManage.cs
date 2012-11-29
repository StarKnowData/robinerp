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

	public partial class FineryIDManage : UiCommon.ManageBasePage
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
		/// Form1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.HtmlControls.HtmlForm Form1;

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
		/// msgLB 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.Label msgLB;

		/// <summary>
		/// FineryIDList 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.Repeater FineryIDList;

		/// <summary>
		/// webfooter1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.UserControl webfooter1;
		public string userid = UiCommon.UserLoginInfo.UserID;
		protected void Page_Load( object sender, EventArgs e )
		{
			DataBinds();
		}

		public void DataBinds()
		{
			string sqltext = "select FineryID,IsUse,IsCopy from Web_FineryID where UserID='" + userid + "' and IsBuy=1";
			DataTable tb = DbSession.Default.FromSql( sqltext ).ToDataTable();
			if( tb.Rows.Count > 0 )
			{
				FineryIDList.DataSource = tb;
				FineryIDList.DataBind();
			}
			else
			{
				this.msgLB.Visible = true;
			}
		}
	}
}
