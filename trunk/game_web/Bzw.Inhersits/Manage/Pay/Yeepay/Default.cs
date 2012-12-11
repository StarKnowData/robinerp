using System;
using System.Data;
using System.Configuration;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using com.yeepay;
using UiCommon;
using BCST.Common;
using Bzw.WebLibrary;
using Utility;
using System.Data.SqlClient;

namespace Bzw.Inhersits.Manage.Pay.Yeepay
{
    public partial class Manage_Pay_Yeepay_Default : UiCommon.BasePage
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
        protected string MoneyRate = string.Empty;
        protected string CouponRate = string.Empty;



        protected void Page_Load(object sender, EventArgs e)
        {
            SeoSetting(SeoConfig.Config.PaySeo);
            if (UiCommon.UserLoginInfo.IsLogin)
            {
                txtUserName.Text = UiCommon.UserLoginInfo.UserName;
                txtUserName2.Text = UiCommon.UserLoginInfo.UserName;
            }
            MoneyRate = BLL.Config.GetInfoOfCard()["Con_MoneyChangeRate"].ToString();
            CouponRate = GetCouponRate();
        }

        protected void Button1_Click(object sender, EventArgs e)
        {
            string errorUrl = "/Manage/Pay/Yeepay/Default.aspx"; //出错跳转地址
            //商品名称（商户）
            string companyName = UiCommon.StringConfig.CompanyNameOfPay;

            //支付人
            string userName = txtUserName.Text.Trim();

            //支付金额
            string payMoney = PayMoney.Text.Trim();

            //支付类型 Web_RMBCost.PayType
            int payTypeLog = 1;

            //类型信息 Web_RMBCost.Typeinfo
            string typeInfoLog = "易宝支付网关支付";

            //与易宝的交易订单号
            string out_trade_no = DateTime.Now.ToString("yyyyMMddHHmmssfffffff");
            BLL.Member mem = new BLL.Member();
            int otherPayMoney = mem.UserTodayOtherPayMoney(userName);
            //是否超出今天充值限制额
            if (Convert.ToInt32(payMoney) > otherPayMoney)
            {
                Response.Write("<script>alert('您今天能充值金额数不能大于" + otherPayMoney + "。');location.href='" + errorUrl + "';</script>");
                Response.End();
            }

            //插入支付订单日志
            new BLL.Member().Add3PayOrder(userName, Convert.ToInt32(payMoney), payTypeLog, typeInfoLog, out_trade_no);


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


            //#region 测试代码
            //p1_MerId = "10000432521";                                     // 商家ID
            //keyValue = "8UPp0KE8sq73zVP370vko7C39403rtK1YwX40Td6irH216036H27Eb12792t";  // 商家密钥
            // 设置请求地址
            //Buy.NodeAuthorizationURL = @"http://tech.yeepay.com:8080/robot/debug.action"; //test 
            //#endregion


            p2_Order = out_trade_no;

            p3_Amt = payMoney;

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
            //p8_Url = "http://localhost:102/user/yeepay/Callback.aspx";//本地测试URLuser/yeepay/Default.aspx

            //p8_Url = UiCommon.StringConfig.WebSiteName + "/Manage/Pay/Yeepay/Callback.aspx";

            p8_Url = UiCommon.StringConfig.WebSiteName + "/Manage/Pay/Yeepay/Callback.aspx";


            //送货地址
            //为“1”: 需要用户将送货地址留在易宝支付系统;为“0”: 不需要，默认为 ”0”.
            p9_SAF = "0";

            //商户扩展信息
            //商户可以任意填写1K 的字符串,支付成功时将原样返回.	
            // [add] jeffery
            double poupon=Convert.ToDouble(CouponRate)*Convert.ToDouble( PayMoney.Text);
            if(poupon<0)
                poupon=0;
            pa_MP = userName + "!@#" + Convert.ToInt32(poupon).ToString();
            // ---end

            //银行编码
            //默认为""，到易宝支付网关.若不需显示易宝支付的页面，直接跳转到各银行、神州行支付、骏网一卡通等支付页面，该字段可依照附录:银行列表设置参数值.
            pd_FrpId = "";


            //应答机制
            //为"1": 需要应答机制;为"0": 不需要应答机制.
            pr_NeedResponse = "1";

            Response.Redirect(Buy.CreateBuyUrl(p1_MerId, keyValue, p2_Order, p3_Amt, p4_Cur, p5_Pid, p6_Pcat, p7_Pdesc, p8_Url, p9_SAF, pa_MP, pd_FrpId, pr_NeedResponse));

        }

        private string GetCouponRate()
        {
            string strsql = "select top 1 CouponRate from TRechargeCouponType where Way=@way";
            DataTable table = SqlHelper.ExecuteDataset(
                CommandType.Text,
                strsql,
                new SqlParameter[]{
                    new SqlParameter("@way",3)
                }
                ).Tables[0];
            if (table.Rows.Count > 0)
            {
                return table.Rows[0]["CouponRate"].ToString();
            }
            return "";
        }


    }
}
