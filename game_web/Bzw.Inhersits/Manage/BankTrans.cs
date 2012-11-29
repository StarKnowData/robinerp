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
using Bzw.Data;
using BCST.Common;
using System.Collections.Generic;


namespace Bzw.Inhersits.Manage
{

    public partial class Manage_BankTrans : UiCommon.ManageBasePage
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
        /// txtInputUserName 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtInputUserName;

        /// <summary>
        /// txtInputUserName2 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtInputUserName2;

        /// <summary>
        /// txtMoney 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtMoney;

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
        /// <summary>
        /// 账户余额必须大于这个数才能转账
        /// </summary>
        public Int64 TransferLessAllMoney = 0;
        /// <summary>
        /// 单笔转账的最小金币数
        /// </summary>
        public Int64 TransferLessMoney = 0;
        /// <summary>
        /// 转账的金币值必须是这个数的倍数
        /// </summary>
        public int TransferMultiple = 0;
        /// <summary>
        /// 转账要扣出的手续费用 0.01表示1%
        /// </summary>
        public int TransferTax = 0;
        /// <summary>
        /// 单笔转账最高扣出的手续费用
        /// </summary>
        public int MaxTransTax = 0;
        /// <summary>
        /// VIP用户转帐要扣除的手续费
        /// </summary>
        public int VipTransferTax = 0;

        BLL.Member member = new BLL.Member();

        protected void Page_Load(object sender, EventArgs e)
        {
            if (member.IsInRoomOrGame(UiCommon.UserLoginInfo.UserName))
            {
                //lblMsg.Text = "抱歉，您的帐号已进入房间中或正在游戏中，不能进行存取款操作！";
                BCST.Common.CommonManager.Web.RegJs(this, "alert('抱歉，您的帐号已进入房间中或正在游戏中，不能进行存取款操作！');location.href='/Manage/';", false);
                return;
            }

            //1.读取表web_config中的转账参数信息
            DataRow dr = BLL.Config.GetInfoOfTrans();
            if (dr != null)
            {
                if (dr["TransferLessAllMoney"] != null)
                {
                    TransferLessAllMoney = Convert.ToInt64(dr["TransferLessAllMoney"]);
                }

                if (dr["TransferLessMoney"] != null)
                {
                    TransferLessMoney = Convert.ToInt32(dr["TransferLessMoney"]);
                }

                if (dr["TransferMultiple"] != null)
                {
                    TransferMultiple = Convert.ToInt32(dr["TransferMultiple"]);
                }

                if (dr["TransferTax"] != null)
                {
                    TransferTax = Convert.ToInt32(dr["TransferTax"]);
                }

                if (dr["MaxTransTax"] != null)
                {
                    MaxTransTax = Convert.ToInt32(dr["MaxTransTax"]);
                }

                if (dr["VipTransferTax"] != null)
                {
                    VipTransferTax = Convert.ToInt32(dr["VipTransferTax"]);
                }
            }
        }

        protected void button5_ServerClick(object sender, EventArgs e)
        {
            if (!BCST.Common.CommonManager.Web.CheckPostSource())
                return;

            string userId = UiCommon.UserLoginInfo.UserID;
            string outUserName = UiCommon.UserLoginInfo.UserName;
            string password = txtPassword.Text.Trim();//hidPwd.Value.Trim(); //
            if (!member.CompareTwoPassword(userId, password))
            {
                lblMsg.Text = "对不起，您输入的银行密码有误！";
                return;
            }

            Int64 outUserBankMoney = member.GetBankMoney(userId);

            string inputUserName = Utility.Common.FilterString(txtInputUserName.Text.Trim());



            //2.判断转出方账号是否在游戏房间或正在游戏中，是则不能进行转账操作！
            if (member.IsInRoomOrGame(outUserName))
            {
                lblMsg.Text = "抱歉，您的帐号已进入房间中或正在游戏中，不能进行转账操作！";
                return;
            }

            //2.1转出方账户余额必须大于这个数TransferLessAllMoney才能转账
            long LeftMoney = member.GetAllMoney(userId);       //获取账户余额 

            if (LeftMoney <= Convert.ToInt64(TransferLessAllMoney))
            {
                lblMsg.Text = "抱歉，您的账户余额必须大于规定的" + UiCommon.StringConfig.AddZeros(TransferLessAllMoney) +UiCommon.StringConfig.MoneyName+ "才能转账！";
                return;

            }

            //3.如果转入方的账号不存在，不能进行转账操作
            if (!member.ExistName(inputUserName))
            {
                lblMsg.Text = "抱歉，您填写的转入帐号不存在！";
                return;
            }

            //4.如果转入方的账号正在游戏中，不能进行转账操作（此项限制可选）
            if (member.IsInRoomOrGame(inputUserName))
            {
                lblMsg.Text = "抱歉，转入方的帐号已进入房间中或正在游戏中，不能进行转账操作！";
                return;
            }

            long transMoney = Convert.ToInt64(txtMoney.Text.Trim());
            //5.1转账金额必须是这个数的倍数TransferMultiple
            if (transMoney % TransferMultiple != 0)
            {
                lblMsg.Text = "抱歉，您输入的转账金额必须是" + TransferMultiple + "的倍数！";
                return;
            }

            transMoney = Convert.ToInt64(UiCommon.StringConfig.RemoveZeros(transMoney));
            //5.2转账金额不能小于单笔转账规定值TransferLessMoney
            if (transMoney < TransferLessMoney)
            {
                lblMsg.Text = "抱歉，您输入的转账金额小于单笔转账规定值" + UiCommon.StringConfig.AddZeros(TransferLessMoney) +UiCommon.StringConfig.MoneyName+ "！";
                return;
            }

            //6.转出方银行帐户余额不足，请存款后在进行转帐！
            if (outUserBankMoney < transMoney)
            {
                lblMsg.Text = "抱歉，您的银行余额不足，请存款或充值后再进行转账！";
                return;
            }

            //transMoney少于零，则说明输入的金额比配置的倍数小。输入的金额至少要达到倍数的额数。2010-01-26
            if (transMoney <= 0)
            {
                lblMsg.Text = "抱歉，转账金额必须大于或等于" + UiCommon.StringConfig.GetMultiple();
                return;
            }

            //7.更新转出方银行存款、更新转入方银行存款、写入转账 Web_TransLog 记录表
            Dictionary<string, object> dic = new Dictionary<string, object>();
            DbSession.Default.FromProc("Web_pBankTrans")
                .AddInputParameter("@outUserName", DbType.String, outUserName)
                .AddInputParameter("@inUserName", DbType.String, inputUserName)
                .AddInputParameter("@transMoney", DbType.Int64, transMoney)
                .AddInputParameter("@transTime", DbType.DateTime, DateTime.Now)
                .AddInputParameter("@transIP", DbType.String, CommonManager.Web.GetIP())
                .AddOutputParameter("@Result", DbType.Int32, 4)
                .Execute(out dic);

            //if( member.BankTransfer( outUserName, inputUserName, transMoney, Utility.Common.RequestIP ) )
            if (dic.Count > 0 && (int)dic["Result"] == 0)
            {
                DateTime tmp_viptime = DbSession.Default.FromSql("select DATEADD([second],viptime,'1970-01-01 08:00:00') from Web_vUserList where UserName=@UserName").AddInputParameter("@UserName", DbType.String, outUserName).ToScalar<DateTime>();

                int taxMoney = 0;// = transMoney;
                if (tmp_viptime > DateTime.Now)
                {
                    //VIP手续费   根据项目实施部要求转账手续费改成千分比  周圣华 2010-05-14
                    taxMoney = (int)((float)transMoney * (((float)VipTransferTax / 10000))); //*= (VipTransferTax / 100);
                }
                else
                {
                    //普通会员手续费
                    taxMoney = (int)((float)transMoney * (((float)TransferTax / 10000))); //*= (TransferTax / 100);
                }

                if (taxMoney > MaxTransTax)
                {
                    taxMoney = MaxTransTax;
                }
                int sjTransMoney = (int)transMoney - taxMoney; //实际转账金额 

                CommonManager.Web.RegJs(this, "alert('转账成功，您转给" + inputUserName + "的" + UiCommon.StringConfig.AddZeros(transMoney) +UiCommon.StringConfig.MoneyName+ "，扣除手续费" + UiCommon.StringConfig.AddZeros(taxMoney) +UiCommon.StringConfig.MoneyName+ "后，" + UiCommon.StringConfig.AddZeros(sjTransMoney) + UiCommon.StringConfig.MoneyName+"已转入他/她的银行账户！');location.href=location.href;", false);
            }
            else if (dic.Count > 0 && (int)dic["Result"] == 1)
            {
                CommonManager.Web.RegJs(this, "alert('您的银行" + UiCommon.StringConfig.MoneyName + "不足，请先去充值后再转帐。');location.href=location.href;", true);
            }
            else if (dic.Count > 0 && (int)dic["Result"] == 3)
            {
                CommonManager.Web.RegJs(this, "alert('抱歉，转账不能自己转给自己，请重新输入转入帐号！');location.href=location.href;", true);
            }
            else
            {
                //lblMsg.Text = "抱歉，转账操作失败，可能是服务器繁忙，请稍候再试！";
                CommonManager.Web.RegJs(this, "alert('抱歉，转账操作失败，可能是服务器繁忙，请稍候再试！');location.href=location.href;", true);
            }
        }
    }
}
