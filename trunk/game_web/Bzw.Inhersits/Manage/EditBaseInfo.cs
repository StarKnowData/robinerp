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
using BCST.Common;

namespace Bzw.Inhersits.Manage
{
    public partial class Manage_EditBaseInfo : UiCommon.ManageBasePage
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
    /// frmLogin 控件。
    /// </summary>
    /// <remarks>
    /// 自动生成的字段。
    /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
    /// </remarks>
    protected global::System.Web.UI.HtmlControls.HtmlForm frmLogin;
    
    /// <summary>
    /// txtPassword 控件。
    /// </summary>
    /// <remarks>
    /// 自动生成的字段。
    /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
    /// </remarks>
    protected global::System.Web.UI.WebControls.TextBox txtPassword;
    
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

        public string NickName = string.Empty;
        public int Sex = 1;
        public string CustImgDir = string.Empty;
        public int LogoID = 0;
        public string Email = string.Empty;
        public string Phone = string.Empty;
        public string qqNum = string.Empty;
        public string needqq = System.Configuration.ConfigurationSettings.AppSettings["qq"];

        protected string province = "";
        protected string city = "";
        protected string OccuPation = "";
        protected string address = "";

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                BindInfo();
            }
        }

        protected void BindInfo()
        {
            BLL.Member member = new BLL.Member();
            DataRow dr = member.GetInfo(UserLoginInfo.UserID);
            if (dr == null)
            {
                return;
            }

            NickName = dr["NickName"].ToString();
            Sex = Convert.ToInt32(dr["Sex"]);
            LogoID = Convert.ToInt32(dr["LogoID"]);
            LogoID = member.GetLogoID(Sex, LogoID);
            if (LogoID > BLL.Member.LogoId_Const2)
            {
                int childDirName = Convert.ToInt32(UserLoginInfo.UserID) / 1000;
                CustImgDir = "/Upload/" + UiCommon.StringConfig.UserCustHeadFolderName + "/" + childDirName + "/" + UserLoginInfo.UserID + ".png";
            }
            Email = dr["Email"].ToString();

            Phone = dr["Phone"].ToString();

            qqNum = dr["qqnum"].ToString();
            OccuPation = dr["OccuPation"].ToString();
            address = dr["AdrZone"].ToString();
            province = dr["AdrProvince"].ToString();
            city = dr["AdrCity"].ToString();
        }

        protected void button5_ServerClick(object sender, EventArgs e)
        {
            BLL.Member member = new BLL.Member();
            string password = Common.GetStringOfForm("txtPassword");//txtPassword.Text.Trim();
            if (!member.CompareLoginPassword(UserLoginInfo.UserID, password))
            {
                //Label1.Text = "对不起，您输入的旧密码有误！";
                CommonManager.Web.RegJs(this, "alert('对不起，您输入的旧密码有误！');location.href=location.href;", true);
                BindInfo();
                return;
            }

            //昵称可以输入任何字符，所以要对它进行HTML编码，防止恶意木马脚本字符串；过滤"'"为"''"，避免SQL注入式攻击
            string nickname = Server.HtmlEncode(Common.GetStringOfForm("nickname").Replace("'", "''"));
            string sex = Common.FilterString(Common.GetStringOfForm("sex"));
            string pwd = Common.FilterString(Common.GetStringOfForm("pwd"));
            string email = Common.FilterString(Common.GetStringOfForm("email"));
            string mobile = Common.FilterString(Common.GetStringOfForm("mobile"));
            string logoid = Common.FilterString(Common.GetStringOfForm("hidLogoID"));
            string qqnum = Common.FilterString(Common.GetStringOfForm("qqnum"));
            logoid = member.SetLogoID(Convert.ToInt32(sex.Trim()), Convert.ToInt32(logoid.Trim())).ToString();

            string _address = Server.HtmlEncode( CommonManager.Web.RequestForm( "txtAddress", "" ) );
            string _province = CommonManager.Web.RequestForm( "hidProvince", "" );
            string _city = CommonManager.Web.RequestForm( "hidCity", "" );
            string _occu = CommonManager.Web.RequestForm( "txtOccuPation", "" );

            //int iRows = member.UpdateBaseInfo(UserLoginInfo.UserID, pwd, nickname, int.Parse(logoid), int.Parse(sex), email, mobile, qqnum);
            int iRows = member.UpdateBaseInfo( UserLoginInfo.UserID, pwd, nickname, int.Parse( logoid ), int.Parse( sex ), email, mobile, _occu, _province, _city, _address,qqnum);
            if (iRows > 0)
            {
                //Label1.Text = "资料修改成功！" + DateTime.Now;
                CommonManager.Web.RegJs(this, "alert('资料修改成功！');location.href=location.href;", true);
                BindInfo();
                /*if (Convert.ToInt32(logoid.Trim()) <= BLL.Member.LogoId_Const2)
                {
                    //trImgType.Attributes.Add("style", "display:none");
                    //tbCust.Attributes.Add("style", "display:none");
                }*/
            }
            else
            {
                //Label1.Text = "抱歉，资料修改失败，可能是服务器繁忙，请稍候再试！";
                CommonManager.Web.RegJs(this, "alert('抱歉，资料修改失败，可能是服务器繁忙，请稍候再试！');location.href=location.href;", true);
            }
        }
    }
    
}
