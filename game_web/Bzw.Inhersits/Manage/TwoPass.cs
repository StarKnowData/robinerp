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

namespace Bzw.Inhersits.Manage
{
    public partial class Manage_TwoPass : UiCommon.ManageBasePage
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
        /// Left1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl Left1;

        /// <summary>
        /// webuserlogin1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webuserlogin1;

        /// <summary>
        /// Form1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlForm Form1;

        /// <summary>
        /// lblMsg 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Label lblMsg;

        /// <summary>
        /// txtPassword 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtPassword;

        /// <summary>
        /// dd_1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlTableRow dd_1;

        /// <summary>
        /// ddlCardType 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.DropDownList ddlCardType;

        /// <summary>
        /// dd_3 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlTableRow dd_3;

        /// <summary>
        /// txtCardNo 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtCardNo;

        /// <summary>
        /// dd_5 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlTableRow dd_5;

        /// <summary>
        /// txtCardNo2 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtCardNo2;

        /// <summary>
        /// dd_7 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlTableRow dd_7;

        /// <summary>
        /// ddlQuestion 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.DropDownList ddlQuestion;

        /// <summary>
        /// dd_9 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlTableRow dd_9;

        /// <summary>
        /// txtAnwer 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtAnwer;

        /// <summary>
        /// dd_11 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlTableRow dd_11;

        /// <summary>
        /// txtOldTwoPass 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtOldTwoPass;

        /// <summary>
        /// txtTwoPass 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtTwoPass;

        /// <summary>
        /// txtTwoPass2 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtTwoPass2;

        /// <summary>
        /// button5 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputSubmit button5;

        /// <summary>
        /// divNotes 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlGenericControl divNotes;

        /// <summary>
        /// divNotes2 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlGenericControl divNotes2;

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
            if (!IsPostBack)
            {
                BindInfo();
            }
        }

        public void BindInfo()
        {
            BindCardType();
            BindQuestion();

            BLL.Member member = new BLL.Member();
            DataRow dr = member.GetInfo(UserLoginInfo.UserID);
            if (dr == null)
            {
                return;
            }
            string dbCardType = dr["ZJ_Type"].ToString();
           txtCardNo.Text = dr["ZJ_Number"].ToString();
            txtCardNo2.Text = txtCardNo.Text;
            string dbQuestion = dr["Pwd_ques"].ToString();
            txtAnwer.Text = dr["Pwd_anw"].ToString();
            string cardNo = dr["ZJ_Number"].ToString().Trim();
            //因为界面上的证件类型、号码、提示问题、答案都是不能为
            //空的，所以，如果证件号码有内容，则其它都有内容，就把这几个输入项隐藏
            if (!string.IsNullOrEmpty(dbQuestion))
            {
                Hidden();
            }


            for (int i = 0; i < ddlCardType.Items.Count; i++)
            {
                if (ddlCardType.Items[i].Value.ToLower() == dbCardType.Trim().ToLower())
                {
                    ddlCardType.SelectedIndex = i;
                    break;
                }
            }

            for (int i = 0; i < ddlQuestion.Items.Count; i++)
            {
                if (ddlQuestion.Items[i].Value.ToLower() == dbQuestion.Trim().ToLower())
                {
                    ddlQuestion.SelectedIndex = i;
                    break;
                }
            }
        }

        public void BindCardType()
        {
            ddlCardType.Items.Add(new ListItem("请选择", "0"));
            ddlCardType.Items[0].Selected = true;
            string[] ctNames = StringConfig.GetCardTypeNames;
            string[] ctValues = StringConfig.GetCardTypeValues;
            for (int i = 0; i < ctNames.Length; i++)
            {
                ddlCardType.Items.Add(new ListItem(ctNames[i], ctValues[i]));
            }
        }

        public void BindQuestion()
        {
            ddlQuestion.Items.Add(new ListItem("请选择", ""));
            ddlQuestion.Items[0].Selected = true;
            string[] quesNames = StringConfig.GetQuestionNames;
            for (int i = 0; i < quesNames.Length; i++)
            {
                ddlQuestion.Items.Add(new ListItem(quesNames[i], quesNames[i]));
            }
        }

        //隐藏证件类型、号码、提示问题、答案输入项
        public void Hidden()
        {
            /*
            dd_1.Attributes.Add("style", "display:none");
            dd_2.Attributes.Add("style", "display:none");
            dd_3.Attributes.Add("style", "display:none");
            dd_4.Attributes.Add("style", "display:none");
            dd_5.Attributes.Add("style", "display:none");
            dd_6.Attributes.Add("style", "display:none");
            dd_7.Attributes.Add("style", "display:none");
            dd_8.Attributes.Add("style", "display:none");
            dd_9.Attributes.Add("style", "display:none");
            dd_10.Attributes.Add("style", "display:none");*/

            /*txtCardNo.Text = string.Empty;
            txtCardNo2.Text = string.Empty;
            txtAnwer.Text = string.Empty;
            //dd_1.Visible = false;
            //dd_2.Visible = false;
            //dd_3.Visible = false;
            //dd_4.Visible = false;
            dd_5.Visible = false;
            //dd_6.Visible = false;
            //dd_7.Visible = false;
            //dd_8.Visible = false;
            //dd_9.Visible = false;
            //dd_10.Visible = false;*/

            dd_1.Visible = false;

            dd_3.Visible = false;

            dd_5.Visible = false;

            dd_7.Visible = false;

            dd_9.Visible = false;

            divNotes.Visible = false;//同时隐藏提示信息
            divNotes2.Style.Add("display", "block"); //

            //如果隐藏上面的项目，则表示已经设置过密保资料，此时仅允许修改二级密码，应要求输入原二级密码，以保护二级密码
            dd_11.Visible = true;


        }

        protected void button5_ServerClick(object sender, EventArgs e)
        {
            if (!BCST.Common.CommonManager.Web.CheckPostSource())
                return;

            BLL.Member member = new BLL.Member();
            //string password = hidPwd2.Value.Trim();//txtPassword.Text.Trim();
            string password = txtPassword.Text.Trim();
            if (!member.CompareLoginPassword(UserLoginInfo.UserID, password))
            {
                lblMsg.Text = "对不起，您输入的登录密码有误！";
                return;
            }

            if (dd_11.Visible)
            {
                if (string.IsNullOrEmpty(txtOldTwoPass.Text.Trim()))
                {
                    lblMsg.Text = "请输入原二级密码！";
                    return;
                }
                if (!member.CompareTwoPassword(UserLoginInfo.UserID, txtOldTwoPass.Text.Trim()))
                {
                    lblMsg.Text = "对不起，您输入的原二级密码有误！";
                    return;
                }
            }

            string cardType = Common.FilterString(ddlCardType.SelectedValue);
            string cardNo = Common.FilterString(txtCardNo.Text.Trim());
            string question = Common.FilterString(ddlQuestion.SelectedValue);
            string answer = Common.FilterString(txtAnwer.Text.Trim());
            string twoPass = Common.FilterString(txtTwoPass.Text.Trim());

            int iRows = 0;
            if (dd_5.Visible)
            {
                iRows = member.UpdateTwoPassInfo(UserLoginInfo.UserID, cardType, cardNo, question, answer, twoPass);
            }
            else if (!string.IsNullOrEmpty(twoPass))
            {
                // iRows = member.UpdateTwoPass(UserLoginInfo.UserID, twoPass);
                iRows = member.UpdateTwoPass(UserLoginInfo.UserID, cardNo, answer, twoPass);
            }
            else
            {
                lblMsg.Text = "银行密码不能为空！" + DateTime.Now;
                return;
            }

            if (iRows > 0)
            {
                if (dd_5.Visible)
                {
                    lblMsg.Text = "银行密码保护资料设置成功！" + DateTime.Now;
                }
                else
                {
                    lblMsg.Text = "银行密码修改成功！" + DateTime.Now;
                }
                Hidden();
                //lblMsg.Text = "银行密码保护资料修改成功！" + DateTime.Now;
                //Hidden();
            }
            else if (iRows == -9)
            {
                lblMsg.Text = "抱歉，您填写的证件号码或问题答案不符，未能修改银行密码，请重新输入！";
                Hidden();
            }
            else
            {
                lblMsg.Text = "抱歉，资料修改失败，可能是服务器繁忙，请稍候再试！";
            }
        }
    }
}
