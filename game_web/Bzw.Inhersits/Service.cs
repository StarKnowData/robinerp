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
using BCST.Common;
using Bzw.WebLibrary;
using UiCommon;

namespace Bzw.Inhersits
{
	public partial class Service : UiCommon.BasePage
	{

		/// <summary>
		/// Head1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.HtmlControls.HtmlHead Head1;

		/// <summary>
		/// webmeta1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.UserControl webmeta1;

		/// <summary>
		/// webtop1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.UserControl webtop1;

		/// <summary>
		/// webuserlogin1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.UserControl webuserlogin1;

		/// <summary>
		/// webservice1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.UserControl webservice1;

		/// <summary>
		/// webshortcutkey1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		//protected global::Public_WebShortCutKey webshortcutkey1;

		/// <summary>
		/// Form1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.HtmlControls.HtmlForm Form1;

		/// <summary>
		/// txtName 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.TextBox txtName;

		/// <summary>
		/// txtEmail 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.TextBox txtEmail;

		/// <summary>
		/// txtTitle 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.TextBox txtTitle;

		/// <summary>
		/// txtContent 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.TextBox txtContent;

		/// <summary>
		/// imageField2 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.HtmlControls.HtmlInputSubmit imageField2;

		/// <summary>
		/// webfooter1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.UserControl webfooter1;
        protected global::System.Web.UI.WebControls.TextBox VerifyCode;



		protected void Page_Load( object sender, EventArgs e )
		{
			SeoSetting( SeoConfig.Config.FAQSeo );
			if( !IsPostBack )
			{
				BindUserInfo();
			}
		}

		public void BindUserInfo()
		{
			if( UiCommon.UserLoginInfo.IsLogin )
			{
				DataRow dr = new BLL.Member().GetInfo( UiCommon.UserLoginInfo.UserID );
				if( dr != null )
				{
					txtName.Text = dr["NickName"].ToString();
					//UiCommon.UserLoginInfo.UserName;
					//txtName.ReadOnly = true;
					txtEmail.Text = dr["Email"].ToString();
				}
			}
		}
		protected void button5_ServerClick( object sender, EventArgs e )
		{
			/*
			string name = Utility.Common.FilterString(txtName.Text);
			string email = Utility.Common.FilterString(txtEmail.Text);
			string title = Utility.Common.FilterString(txtTitle.Text);
			string content = Utility.Common.FilterString(txtContent.Text);*/

			string name = Server.HtmlEncode( Utility.Common.SqlEncode( txtName.Text ) );
			string email = Utility.Common.FilterString( txtEmail.Text );
			string title = Server.HtmlEncode( Utility.Common.SqlEncode( txtTitle.Text ) );
			string content = Server.HtmlEncode( Utility.Common.SqlEncode( txtContent.Text ) );

            string verify = VerifyCode.Text;
            if (ValidCode.CurrentCode != verify)
            {

                CommonManager.Web.RegJs(this, "alert('温馨提示：验证码输入错误，请重新输入！');", true);
                return;
            }



			int iRows = new BLL.Feedback().Add( name, email, title, content, Utility.Common.RequestIP );
			if( iRows > 0 )
			{
				if( UiCommon.UserLoginInfo.IsLogin )
					Response.Redirect( "/Manage/Feedbacks.aspx" );
				else
					CommonManager.Web.RegJs( this, "location.href='Service.aspx?success';", false );
			}
			else
				CommonManager.Web.RegJs( this, "location.href='Service.aspx?fail';", false );

			//if (iRows > 0)
			//{
			//    lblMsg.Text = "留言提交成功!"+DateTime.Now;
			//    if (UiCommon.UserLoginInfo.IsLogin)
			//    {
			//        Response.Redirect("/Manage/Feedbacks.aspx");
			//    }
			//    else
			//    {
			//        txtName.Text = string.Empty;
			//        txtEmail.Text = string.Empty;
			//        txtTitle.Text = string.Empty;
			//        txtContent.Text = string.Empty;
			//    }
			//}
			//else
			//{
			//    lblMsg.Text = "抱歉，留言提交失败，可能是服务器繁忙，请稍候再试！";
			//}
		}
	}

}
