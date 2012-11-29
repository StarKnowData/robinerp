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

namespace Bzw.Inhersits.Manage
{
    public partial class Manage_Login : UiCommon.BasePage
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
        /// form1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlForm form1;

        /// <summary>
        /// webtop1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webtop1;

        /// <summary>
        /// webservice1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webservice1;



        /// <summary>
        /// lbMsg 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Label lbMsg;

        /// <summary>
        /// txtAccount 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtAccount;

        /// <summary>
        /// txtPwd 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtPwd;

        /// <summary>
        /// txtValidCode 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtValidCode;

        /// <summary>
        /// imageField 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Button imageField;

        /// <summary>
        /// webfooter1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webfooter1;
        protected void Page_Load(object sender, EventArgs e)
        {
            SeoSetting(SeoConfig.Config.DefaultSeo);
            //如果已登录则回到首页
            if (UiCommon.UserLoginInfo.IsLogin)
            {
                Response.Redirect("/Default.aspx");
            }
        }
        protected void btnSubmit_Click(object sender, EventArgs e)
        {
            lbMsg.Text = "对不起，访问服务器出错，请稍候再试！";

            //1.校验验证码
            if (UiCommon.ValidCode.CurrentCode == null)
            {
                lbMsg.Text = "验证码已过期，请输入新的验证码！";
                txtValidCode.Text = string.Empty;
                return;
            }
            else if (txtValidCode.Text.Trim() != UiCommon.ValidCode.CurrentCode)
            {
                lbMsg.Text = "验证码输入错误，请输入新的验证码！";
                txtValidCode.Text = string.Empty;
                return;
            }


            string userName = Utility.Common.FilterString(txtAccount.Text);
            string pass = Utility.Common.FilterString(txtPwd.Text); //Utility.Common.FilterString( hidPwd.Value.Trim() );//

            BLL.LoginResults lr = new BLL.Member().Login(userName, pass);
            if (lr == BLL.LoginResults.MemberNameInvalid)
            {
                lbMsg.Text = "用户名错误！";
                txtValidCode.Text = string.Empty;
            }
            if (lr == BLL.LoginResults.PasswordInvalid)
            {
                lbMsg.Text = "密码错误！";
                txtValidCode.Text = string.Empty;
            }
            else if (lr == BLL.LoginResults.Locked)
            {
                lbMsg.Text = "您的帐号已经被管理员限制，不能登录！";
                txtValidCode.Text = string.Empty;
            } 
            else if (lr == BLL.LoginResults.Succeed)
            {
                new BLL.Member().UpdateLastLogin(userName, Utility.Common.RequestIP);

                string backUrl = Utility.Common.UrlValue;
                if (backUrl.Trim().Length == 0)
                {
                    backUrl = "/Manage/Default.aspx";
                }
                if (backUrl.Trim() == UiCommon.StringConfig.WebSiteName+"/Default2.aspx")
                {
                    backUrl = "/Manage/Default.aspx";
                }
                Response.Redirect(backUrl);
            }

            //lbMsg.Visible = true;
        }
    }
}
