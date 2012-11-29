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
namespace Bzw.Inhersits.Manage
{
    public partial class Manage_GetPassAnswer : UiCommon.BasePage
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
        /// form1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlForm form1;

        /// <summary>
        /// lblMsg 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Label lblMsg;

        /// <summary>
        /// ddlCardType 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.DropDownList ddlCardType;

        /// <summary>
        /// txtCardNo 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtCardNo;

        /// <summary>
        /// ddlQuestion 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.DropDownList ddlQuestion;

        /// <summary>
        /// txtAnwer 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtAnwer;

        /// <summary>
        /// txtTwoPass 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtTwoPass;

        /// <summary>
        /// button5 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputSubmit button5;

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
            if (Session["getpwduser"] == null)
            {
                Response.Redirect("/Manage/GetPass.aspx");
            }

            BindCardType();
            BindQuestion();

            BLL.Member member = new BLL.Member();
            DataRow dr = member.GetInfoByName(Session["getpwduser"].ToString());
            if (dr == null)
            {
                return;
            }
            string dbCardType = dr["ZJ_Type"].ToString();
            //txtCardNo.Text = dr["ZJ_Number"].ToString();
            //txtCardNo2.Text = txtCardNo.Text;
            string dbQuestion = dr["Pwd_ques"].ToString();
            //txtAnwer.Text = dr["Pwd_anw"].ToString();

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
            string[] ctNames = UiCommon.StringConfig.GetCardTypeNames;
            string[] ctValues = UiCommon.StringConfig.GetCardTypeValues;
            for (int i = 0; i < ctNames.Length; i++)
            {
                ddlCardType.Items.Add(new ListItem(ctNames[i], ctValues[i]));
            }
        }

        public void BindQuestion()
        {
            ddlQuestion.Items.Add(new ListItem("请选择", ""));
            ddlQuestion.Items[0].Selected = true;
            string[] quesNames = UiCommon.StringConfig.GetQuestionNames;
            for (int i = 0; i < quesNames.Length; i++)
            {
                ddlQuestion.Items.Add(new ListItem(quesNames[i], quesNames[i]));
            }
        }

        protected void button5_ServerClick(object sender, EventArgs e)
        {
            string backUrl = "/Manage/GetPass.aspx";

            if (Session["getpwduser"] == null)
            {
                Response.Redirect(backUrl);
            }

            string userName = Utility.Common.SqlEncode(Session["getpwduser"].ToString());
            if (txtCardNo.Text.Trim().Length == 0)
            {
                Response.Redirect(backUrl);
            }
            string cardNo = txtCardNo.Text;

            if (txtAnwer.Text.Trim().Length == 0)
            {
                Response.Redirect(backUrl);
            }
            string answer = txtAnwer.Text;

            //if (hidPwd.Value.Trim().Length == 0)
            //{
            //    Response.Redirect(backUrl);
            //}
            string twoPassword = txtTwoPass.Text; //hidPwd.Value.Trim();


            bool flg = new BLL.Member().ValidGetPassAnswer(userName, cardNo, answer, twoPassword);
            if (flg)
            {
                Session["getpwdanswer"] = "pass";
                Response.Redirect("/Manage/GetPassModify.aspx");
            }
            else
            {
                lblMsg.Text = "抱歉，身份证号、问题答案、银行密码的其中一个或多个回答错误！";
            }
        }
    }
}
