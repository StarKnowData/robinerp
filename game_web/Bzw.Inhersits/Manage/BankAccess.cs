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
using System.Collections.Generic;
using Bzw.Data;
using BCST.Common;

namespace Bzw.Inhersits.Manage
{

    public partial class Manage_BankAccess : UiCommon.ManageBasePage
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
        /// lteBank 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Literal lteBank;

        /// <summary>
        /// lteWallet 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Literal lteWallet;

        /// <summary>
        /// rdoType 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.RadioButtonList rdoType;

        /// <summary>
        /// txtTwoPassword 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtTwoPassword;

        /// <summary>
        /// txtMoney 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtMoney;
        /// <summary>
        /// txtMoney2 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtMoney2;

        /// <summary>
        /// button5 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputSubmit button5;

        /// <summary>
        /// ddlGame 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.DropDownList ddlGame;

        /// <summary>
        /// rpList 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Repeater rpList;

        /// <summary>
        /// anpPageIndex 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::Wuqi.Webdiyer.AspNetPager anpPageIndex;

        /// <summary>
        /// webfooter1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webfooter1;

        BLL.Member member = new BLL.Member();
        public int Rowid = 0;

        protected int PageIndex
        {
            get
            {
                string pi = CommonManager.Web.Request("page", "");
                if (string.IsNullOrEmpty(pi) || !CommonManager.String.IsInteger(pi))
                    return 1;
                return int.Parse(pi);
            }
        }	
        protected void Page_Load(object sender, EventArgs e)
        {
            if (member.IsInRoomOrGame(UiCommon.UserLoginInfo.UserName))
            {
                //lblMsg.Text = "抱歉，您的帐号已进入房间中或正在游戏中，不能进行存取款操作！";
                BCST.Common.CommonManager.Web.RegJs(this, "alert('抱歉，您的帐号已进入房间中或正在游戏中，不能进行存取款操作！');history.back();", true);
                return;
            }

            if (!IsPostBack)
            {
                BindUserMoney();
            }
        }

        public void BindUserMoney()
        {
            if (UiCommon.StringConfig.BankVersion == "1")
            {
                lteBank.Text = UiCommon.StringConfig.AddZeros(member.GetBankMoney(UiCommon.UserLoginInfo.UserID));
                lteWallet.Text = UiCommon.StringConfig.AddZeros(member.GetWalletMoney(UiCommon.UserLoginInfo.UserID));
            }
            else
            {
                lteBank.Text = UiCommon.StringConfig.AddZeros(member.GetBankMoney(UiCommon.UserLoginInfo.UserID));
                //绑定游戏列表
                DataTable ds1 = DbSession.Default.FromSql("SELECT * FROM dbo.TGameNameInfo").ToDataTable();
                if (ds1.Rows.Count > 0)
                {
                    ddlGame.DataSource = ds1;

                    ddlGame.DataTextField = "ComName";
                    ddlGame.DataValueField = "NameID";
                    ddlGame.DataBind();
                }

                DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
           .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
           .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
           .AddInputParameter("@Columns", DbType.String, "*")
           .AddInputParameter("@TableName", DbType.String, "Web_VUserGameMoney")
           .AddInputParameter("@Wheres", DbType.String, " and userid="+UiCommon.UserLoginInfo.UserID)
           .AddInputParameter("@KeyName", DbType.String, "GameID")
           .AddInputParameter("@OrderBy", DbType.String, "GameID")
           .ToDataSet();
                if (ds.Tables.Count > 0 && ds.Tables[1].Rows.Count > 0)
                {
                    anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
                    anpPageIndex.CurrentPageIndex = PageIndex;

                    rpList.DataSource = ds.Tables[1];
                    rpList.DataBind();
                    rpList.Visible = true;

                }
                else
                {
                    rpList.Visible = false;
                }		
            }
        }

        protected void button5_ServerClick(object sender, EventArgs e)
        {

            if (string.IsNullOrEmpty(txtTwoPassword.Text.Trim()))
            {
                lblMsg.Text = "请输入银行密码！";
                return;
            }
            if (!member.CompareTwoPassword(UiCommon.UserLoginInfo.UserID, txtTwoPassword.Text.Trim()))
            {
                lblMsg.Text = "对不起，您输入的银行密码不正确！";
                return;
            }
            int opType = Convert.ToInt32(rdoType.SelectedValue);

           
            long ioMoney=0;
            int GameNameID=0;
            if (UiCommon.StringConfig.BankVersion == "1")
            {
                if (Convert.ToInt64(txtMoney.Text.Trim()) <= 0)
                {
                    lblMsg.Text = "存取金额必须是大于零的整数！";
                    return;
                }
                ioMoney = Convert.ToInt64(UiCommon.StringConfig.RemoveZeros(txtMoney.Text.Trim()));
            }
            else
            {
                if (Convert.ToInt64(txtMoney2.Text.Trim()) <= 0)
                {
                    lblMsg.Text = "存取金额必须是大于零的整数！";
                    return;
                }
                opType = 0;
                GameNameID=Convert.ToInt32( ddlGame.SelectedValue);
                ioMoney = Convert.ToInt64(UiCommon.StringConfig.RemoveZeros(txtMoney2.Text.Trim()));
            }
            //ioMoney少于零，则说明输入的金额比配置的倍数小。输入的金额至少要达到倍数的额数。
            if (ioMoney <= 0)
            {
                lblMsg.Text = "抱歉，金额必须大于或等于" + UiCommon.StringConfig.GetMultiple();
                return;
            }

            Dictionary<string, object> dic = new Dictionary<string, object>();
            DbSession.Default.FromProc("Web_pBankMoneyOpera")
                .AddInputParameter("@UserID", DbType.Int32, UiCommon.UserLoginInfo.UserID)
                .AddInputParameter("@MoneyQuantity", DbType.Int64, ioMoney)
                .AddInputParameter("@IsSave", DbType.Int32, opType)
                .AddInputParameter("@NameID", DbType.Int32, GameNameID)
                .AddReturnValueParameter("@ReturnValue", DbType.Int32)
                .Execute(out dic);
            string location = string.Empty;
            if (dic.Count > 0)
            {
                string msg = string.Empty;
                switch ((int)dic["ReturnValue"])
                {
                    case 1:
                        msg = "操作成功！";
                        location = "location.href=location.href;";
                        break;

                    case -1:
                    default:
                        msg = "抱歉，服务器出现未知错误，请稍后重试！";
                        break;
                    case -2:
                        msg = "存款：您输入的存取金额不能大于钱包中的余款！";
                        break;
                    case -3:
                        msg = "取款：您输入的存取金额不能大于银行中的存款！";
                        break;
                }
                CommonManager.Web.RegJs(this, "alert('" + msg + "');" + location, true);
            }
            else
            {
                CommonManager.Web.RegJs(this, "alert('抱歉，服务器出现未知错误，请稍后重试！');history.back();", false);
            }
        }
    }
}
