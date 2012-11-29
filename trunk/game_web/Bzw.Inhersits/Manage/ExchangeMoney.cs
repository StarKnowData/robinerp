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
using UiCommon;
using Bzw.Entities;
using Bzw.Data;
using Bzw.E;

namespace Bzw.Inhersits.Manage
{
    public partial class Manage_ExchangeMoney : UiCommon.ManageBasePage
    {

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
        /// Form1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlForm Form1;

        /// <summary>
        /// txtPassword 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtPassword;

        /// <summary>
        /// RequiredFieldValidator1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.RequiredFieldValidator RequiredFieldValidator1;

        /// <summary>
        /// CustomValidator1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.CustomValidator CustomValidator1;

        /// <summary>
        /// txtAgent 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtAgent;

        /// <summary>
        /// RequiredFieldValidator2 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.RequiredFieldValidator RequiredFieldValidator2;

        /// <summary>
        /// txtAgent2 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtAgent2;

        /// <summary>
        /// RequiredFieldValidator3 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.RequiredFieldValidator RequiredFieldValidator3;

        /// <summary>
        /// CompareValidator1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.CompareValidator CompareValidator1;

        /// <summary>
        /// CustomValidator2 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.CustomValidator CustomValidator2;

        /// <summary>
        /// txtMoney 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtMoney;

        /// <summary>
        /// RequiredFieldValidator4 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.RequiredFieldValidator RequiredFieldValidator4;

        /// <summary>
        /// CompareValidator2 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.CompareValidator CompareValidator2;

        /// <summary>
        /// btnSubmit 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Button btnSubmit;

        /// <summary>
        /// webfooter1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webfooter1;
        /// <summary>
        /// 最低转帐金额
        /// </summary>
        protected string MinMoney = "";
        /// <summary>
        /// 手续费收取方式
        /// </summary>
        protected string ChangeType = "";
        /// <summary>
        /// 手续费金币数量或计算公式
        /// </summary>
        protected string ProcedureFee = "";

        private string _filePath = "/Upload/ProcedureFee.config";

        /// <summary>
        /// 文件路径
        /// </summary>
        private string FilePath
        {
            get
            {
                return Server.MapPath(_filePath);
            }
        }


        protected void Page_Load(object sender, EventArgs e)
        {
            //读取配置文件，初始化页面
            XmlOperator xo = new XmlOperator(_filePath);
            if (!xo.HasDocument)
            {
                CommonManager.Web.RegJs(this, "alert('本功能尚未开通，请稍候再尝试进入此页。');history.back();", false);
                return;
            }
            MinMoney = xo.GetNodeValue("MinMoney");
            ChangeType = xo.GetNodeValue("Type") == "0" ? "固定额" : "百分比";
            ProcedureFee = xo.GetNodeValue("Type") == "0" ? xo.GetNodeValue("StaticValue") : "(交易额×" + xo.GetNodeValue("PercentValue") + "%)";
        }

        protected void btnSubmit_Click(object sender, EventArgs e)
        {
            if (!CommonManager.Web.CheckPostSource())
                return;
            if (!IsValid)
                return;

            //0、服务端校验
            #region 服务端校验
            //读取配置文件
            XmlOperator xo = new XmlOperator(_filePath);
            if (!xo.HasDocument)
            {
                CommonManager.Web.RegJs(this, "alert('本功能尚未开通，请稍候再尝试进入此页。');history.back();", false);
                return;
            }
            if (string.IsNullOrEmpty(txtPassword.Text.Trim()))
            {
                CommonManager.Web.RegJs(this, "alert('请输入您的当前密码！');", false);
                return;
            }
            TUsers user = DbSession.Default.Get<TUsers>(TUsers._.UserID == UserLoginInfo.UserID);
            if (user.Pass != CommonManager.String.EncryptMD5SystemDefaultMethod(txtPassword.Text.Trim(), false, true))
            {
                CommonManager.Web.RegJs(this, "alert('您输入的密码不正确，请重新输入。');", false);
                return;
            }
            if (string.IsNullOrEmpty(txtAgent.Text.Trim()) || string.IsNullOrEmpty(txtAgent2.Text.Trim()) || txtAgent.Text.Trim() != txtAgent2.Text.Trim())
            {
                CommonManager.Web.RegJs(this, "alert('请正确输入代理商帐号');", false);
                return;
            }
            else if (!DbSession.Default.Exists<Web_Agent>(Web_Agent._.LoginName == txtAgent.Text.Trim()))
            {
                CommonManager.Web.RegJs(this, "alert('代理商帐号不存在，请重新核对！');", false);
                return;
            }
            if (string.IsNullOrEmpty(txtMoney.Text.Trim()) || !CommonManager.String.IsInteger(txtMoney.Text.Trim()))
            {
                CommonManager.Web.RegJs(this, "alert('请正确输入要转帐的金币！');", false);
                return;
            }
            #endregion
            //1、检查用户输入的金额
            #region 检查用户输入的金额
            int money = int.Parse(txtMoney.Text.Trim());
            BLL.Member m = new BLL.Member();
            Int64 bmoney = m.GetBankMoney(user.UserID.ToString());
            if (money > bmoney)
            {
                CommonManager.Web.RegJs(this, "alert('您的银行金币余额只有" + bmoney.ToString() == "0" ? "0" : bmoney.ToString() + UiCommon.StringConfig.AddZero() + "，请重新输入。');", false);
                return;
            }
            int minmoney = int.Parse(xo.GetNodeValue("MinMoney"));
            if (money <= minmoney)
            {
                CommonManager.Web.RegJs(this, "alert('每次兑换金币数量必须大于" + minmoney.ToString() + "00！');", false);
                return;
            }
            #endregion
            //2、取得代理商游戏帐户
            #region 取得代理商游戏帐户
            Web_VAgentUserInfo agent = DbSession.Default.Get<Web_VAgentUserInfo>(Web_VAgentUserInfo._.LoginName == txtAgent.Text.Trim());
            if (agent == null)
            {
                CommonManager.Web.RegJs(this, "alert('代理商帐号不存在，请重新核对！');", false);
                return;
            }
            #endregion
            //3、转帐
            //3.1、检测玩家帐号是否在游戏中
            #region 检测玩家帐号是否在游戏中
            if (m.IsInRoomOrGame(UserLoginInfo.UserName))
            {
                CommonManager.Web.RegJs(this, "alert('您的帐号正在游戏中，请先退出游戏再进行操作。');", false);
                return;
            }
            #endregion
            //3.2、检测代理商帐号是否在游戏中
            #region 检测代理商帐号是否在游戏中
            if (m.IsInRoomOrGame(agent.UserName))
            {
                CommonManager.Web.RegJs(this, "alert('代理商帐号正在游戏中，本次兑换不能进行，请稍后尝试。');", false);
                return;
            }
            #endregion
            //3.3、开始转账
            #region 开始转账
            //3.3.1、计算实际到账金币，读取配置文件中的手续费方式
            string type = xo.GetNodeValue("Type");
            //3.3.2、计算手续费
            int profee = type == "0" ? int.Parse(xo.GetNodeValue("StaticValue")) : (int)((float)money * (float.Parse(xo.GetNodeValue("PercentValue")) / 100));
            //3.3.3、计算实际到账金币
            int amoney = money - profee;


            //3.3.4、转帐
            //if( m.BankTransfer( UserLoginInfo.UserName, agent.UserName, amoney, CommonManager.Web.GetIP() ) )
            //{
            //    //3.4、记录转帐日志
            //    Web_AgentMoneyLog log = new Web_AgentMoneyLog();
            //    log.ActuallyMoney = amoney;
            //    log.AgentID = agent.ID;
            //    log.InputDate = DateTime.Now;
            //    log.Money = money;
            //    log.ProcedureFee = profee;
            //    log.UserID = int.Parse( UserLoginInfo.UserID );
            //    DbSession.Default.Save<Web_AgentMoneyLog>( log );
            //    //4、提示信息，转向日志记录页面
            //    CommonManager.Web.RegJs( this, "alert('兑换成功！');location.href='ExchangeMoneyLog.aspx';", false );
            //}
            //else
            //{
            //    //4、提示信息
            //    CommonManager.Web.RegJs( this, "alert('兑换失败，可能是网络原因，请稍后尝试。');", false );
            //}
            #endregion
        }
    }
}
