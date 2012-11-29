using System;
using System.Collections.Generic;
using System.Text;
using BCST.Common;
using UiCommon;
using com.yeepay;
using System.Data;
using Bzw.Data;
using System.Configuration;
using Bzw.WebLibrary;

namespace Bzw.Inhersits.Manage.Pay.Yeepay2
{
    public class Manage_Pay_Yeepay2_Yeepay : UiCommon.BasePage
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
        /// txtUserName 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtUserName;

        /// <summary>
        /// txtUserName2 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtUserName2;

        /// <summary>
        /// PayMoney 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox PayMoney;

        /// <summary>
        /// Button1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputSubmit Button1;

        /// <summary>
        /// webfooter1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webfooter1;

        protected global::System.Web.UI.WebControls.RadioButtonList rtype;
        protected global::System.Web.UI.WebControls.RadioButtonList rtypeBank;
        protected global::System.Web.UI.WebControls.HiddenField hidType;
        /// <summary>
        /// ddlGameList 控件
        /// </summary>
        protected global::System.Web.UI.WebControls.DropDownList ddlGameList;

        protected global::System.Web.UI.WebControls.RadioButtonList rblPayType;

        public string Params = string.Empty;
        protected string payType = string.Empty;
        protected string MoneyRate = string.Empty;
        protected string MoneyToPointRate = string.Empty;
        private string p1_MerId = "";
        private string keyValue = "";
        private string p2_Order = "";
        private string p3_Amt = "";
        private string p4_Cur = "";
        private string p5_Pid = "";
        private string p6_Pcat = "";

        private string p7_Pdesc = "";
        private string p8_Url = "";
        private string p9_SAF = "";
        private string pa_MP = "";
        private string pd_FrpId = "";
        private string pr_NeedResponse = "";


        protected void Page_Load(object sender, EventArgs e)
        {

            #region 加载。。。
            SeoSetting(SeoConfig.Config.PaySeo);
            if (!IsPostBack)
            {

                if (UiCommon.UserLoginInfo.IsLogin)
                {
                    txtUserName.Text = UiCommon.UserLoginInfo.UserName;
                    txtUserName2.Text = UiCommon.UserLoginInfo.UserName;
                }
                Params = CommonManager.Web.Request("params", "").Trim();

                if (Params.ToLower() != "bank")
                {
                    rtype.SelectedValue = Params;
                }
                else
                {
                    rtypeBank.SelectedIndex = 0;
                }
                hidType.Value = Params;
                DataRow dr = BLL.Config.GetInfoOfCard();
                MoneyRate = dr["Con_MoneyChangeRate"].ToString();
                MoneyToPointRate = dr["Con_PointChangeRate"].ToString();
                string bankCode = CommonManager.Web.Request("params", "").Trim(); ;
                if (bankCode.ToUpper() == "BANK")
                {
                    payType = "网银充值";

                }
                //1.获取充值方式
                switch (bankCode.ToLower())
                {
                    case "szx-net":
                        payType = "神州行充值卡充值";
                        break;
                    case "unicom-net":
                        payType = "联通卡充值";
                        break;
                    case "ypcard-net":
                        payType = "易宝一卡通充值";

                        break;
                    case "bank":
                        payType = "银行卡充值";

                        break;
                    case "zhengtu-net":
                        payType = "征途游戏卡充值";

                        break;
                    case "sndacard-net":
                        payType = "盛大游戏卡充值";

                        break;
                    case "qqcard-net":
                        payType = "Q币支付";

                        break;
                    case "junnet-net":
                        payType = "全国骏网一卡通充值";
                        break;

                }
                DataTable dt = DbSession.Default.FromSql("SELECT NameID,ComName FROM dbo.TGameNameInfo WHERE NameID IN (SELECT GameNameID FROM dbo.TGameRoomInfo WHERE GameTypeID=1 GROUP BY GameNameID) ORDER BY dbo.TGameNameInfo.IDSort").ToDataTable();

                if (dt.Rows.Count > 0)
                {

                    ddlGameList.DataSource = dt;
                    ddlGameList.DataTextField = "ComName";
                    ddlGameList.DataValueField = "NameID";
                    ddlGameList.DataBind();
                }
            }
            #endregion
           
        }


        protected void Button1_Click(object sender, EventArgs e)
        {

            //非法操作时重定向的URL地址
            //     string toUrl = "/Manage/Pay/Yeepay2/Default.aspx";
            //银行支付通道编码
            //与易宝的交易订单号
            string out_trade_no = string.Empty;

            string bankCode = CommonManager.Web.Request("params", "").Trim();

            if (bankCode.ToUpper() == "BANK")   //网银充值
            {
                bankCode = CommonManager.Web.RequestForm("rtypeBank", "").ToUpper();
                payType = "银行卡充值";
                out_trade_no = DateTime.Now.ToString("yyyyMMddHHmmssfffffff");
            }
            else  //点卡充值
            {
                bankCode = CommonManager.Web.RequestForm("rtype", "").ToUpper();
                out_trade_no ="ka" + DateTime.Now.ToString("yyMMddHHmmssfffffff");
                switch (bankCode.ToLower())
                {
                    case "szx-net":
                        payType = "神州行充值卡充值";
                        break;
                    case "unicom-net":
                        payType = "联通卡充值";
                        break;
                    case "ypcard-net":
                        payType = "易宝一卡通充值";
                        break;
                    case "zhengtu-net":
                        payType = "征途游戏卡充值";
                        break;
                    case "sndacard-net":
                        payType = "盛大游戏卡充值";
                        break;
                    case "qqcard-net":
                        payType = "Q币支付";
                        break;
                    case "junnet-net":
                        payType = "全国骏网一卡通充值";
                        break;

                }
            }

         
            BLL.Member mem = new BLL.Member();
            string userName = txtUserName.Text.Trim();
            //判断输入的用户是否存在
            if (!mem.ExistName(userName))
            {
                Response.Write("<script>alert('找不到您要充值的用户帐号，请检查输入是否有误');history.go(-1);</script>");
                Response.End();
            }
            //判断玩家充值时，不能在游戏中
            if (mem.IsInRoomOrGame(userName))
            {
                Response.Write("<script>alert('要充值的帐号正在游戏中，请先退出游戏再进行充值');history.go(-1);</script>");
                Response.End();
                 
            }
            string money = PayMoney.Text.Trim();
            //判断面值是否正确
            if (string.IsNullOrEmpty(money) || !CommonManager.String.IsInteger(money) || int.Parse(money) <= 0)
            {
                CommonManager.Web.RegJs(this, "alert('金额只能输入大于0的整数。');history.back();", false);
                return;
            }

            int otherPayMoney = mem.UserTodayOtherPayMoney(userName);
            //是否超出今天充值限制额
            if (Convert.ToInt32(money) > otherPayMoney)
            {
                Response.Write("<script>alert('您今天能充值金额数不能大于" + otherPayMoney + "。');history.go(-1);</script>");
                Response.End();
            }


            //接收第三方支付平台返回支付结果的页面地址，为绝对地址
            string receivePageUrl = UiCommon.StringConfig.WebSiteName + "/Manage/pay/Yeepay2/Return.aspx";
            //商品名称（商户）
            string companyName = UiCommon.StringConfig.CompanyNameOfPay;
            //支付类型 Web_RMBCost.PayType
            int payTypeLog = 3;


            //类型信息 Web_RMBCost.Typeinfo
            string typeInfoLog = "易宝支付_" + payType;

         
            //插入支付订单日志
           //by YMH 2012-9-5  充值积分
           //积分充值存在
            if (ConfigurationManager.AppSettings["IsPayToPoint"] == "1" && rblPayType.SelectedValue == "point" && ddlGameList.SelectedValue != "")
            {
                pa_MP = "2"; //充积分
                new BLL.Member().Add3PayOrder(userName, Convert.ToInt32(money), typeInfoLog, out_trade_no,ddlGameList.SelectedValue);

            }
            else
            {
                pa_MP = "0"; //充金币
                new BLL.Member().Add3PayOrder(userName, Convert.ToInt32(money), payTypeLog, typeInfoLog, out_trade_no);
            }
            //开始调用支付网关

           

            //设置编码
            Response.ContentEncoding = System.Text.Encoding.GetEncoding("GB2312");


            //#if !debug
            #region 正式代码
            p1_MerId = StringConfig.YeepayMerID;                                     // 商家ID
            keyValue = StringConfig.YeepayKey;  // 商家密钥
            Buy.NodeAuthorizationURL = StringConfig.YeepayNodeAuthorizationURL;
            #endregion
            //#endif


            p2_Order = out_trade_no;

            p3_Amt = money;

            //交易币种,固定值"CNY".
            p4_Cur = "CNY";

            //商品名称
            //用于支付时显示在易宝支付网关左侧的订单产品信息.
            p5_Pid = "";

            //商品种类
            p6_Pcat = "";

            //商品描述
            p7_Pdesc = "";
            //商户接收支付成功数据的地址,支付成功后易宝支付会向该地址发送两次成功通知.
            p8_Url = UiCommon.StringConfig.WebSiteName + "/Manage/Pay/Yeepay2/Return.aspx";
            //送货地址
            //为“1”: 需要用户将送货地址留在易宝支付系统;为“0”: 不需要，默认为 ”0”.
            p9_SAF = "0";

            //商户扩展信息
            //商户可以任意填写1K 的字符串,支付成功时将原样返回.	用这个字段判断是否是点卡 点卡手续费20%
            //   pa_MP = "";

            //银行编码
            //默认为""，到易宝支付网关.若不需显示易宝支付的页面，直接跳转到各银行、神州行支付、骏网一卡通等支付页面，该字段可依照附录:银行列表设置参数值.
            pd_FrpId = bankCode;


            //应答机制
            //为"1": 需要应答机制;为"0": 不需要应答机制.
            pr_NeedResponse = "1";

           // Response.Write(p1_MerId.ToString() + " <br> " + keyValue.ToString() + " <br> " + p2_Order.ToString() + " <br> " + p3_Amt.ToString() + " <br> " + p4_Cur.ToString() + " <br> " + p5_Pid.ToString() + " <br> " + p6_Pcat.ToString() + " <br> " + p7_Pdesc.ToString() + " <br> " + p8_Url.ToString() + " <br> " + p9_SAF.ToString() + " <br> " + pa_MP.ToString() + " <br> " + pd_FrpId.ToString() + " <br> " + pr_NeedResponse);
           // Response.End();

            Response.Redirect(Buy.CreateBuyUrl(p1_MerId, keyValue, p2_Order, p3_Amt, p4_Cur, p5_Pid, p6_Pcat, p7_Pdesc, p8_Url, p9_SAF, pa_MP, pd_FrpId, pr_NeedResponse));
        }

    }
}
