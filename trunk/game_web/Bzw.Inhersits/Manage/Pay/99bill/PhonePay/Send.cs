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

using System.Text;
namespace Bzw.Inhersits.Manage.Pay._99bill.PhonePay
{
    public partial class Manage_Pay_99bill_PhonePay_Send : UiCommon.BasePage
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
        /// Lab_productName 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Literal Lab_productName;

        /// <summary>
        /// Lab_orderId 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Literal Lab_orderId;

        /// <summary>
        /// Lab_payerName 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Literal Lab_payerName;

        /// <summary>
        /// Lab_orderAmount 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Literal Lab_orderAmount;

        /// <summary>
        /// inputCharset 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden inputCharset;

        /// <summary>
        /// bgUrl 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden bgUrl;

        /// <summary>
        /// pageUrl 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden pageUrl;

        /// <summary>
        /// version 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden version;

        /// <summary>
        /// language 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden language;

        /// <summary>
        /// signType 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden signType;

        /// <summary>
        /// merchantAcctId 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden merchantAcctId;

        /// <summary>
        /// payerName 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden payerName;

        /// <summary>
        /// payerContactType 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden payerContactType;

        /// <summary>
        /// payerContact 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden payerContact;

        /// <summary>
        /// orderId 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden orderId;

        /// <summary>
        /// orderAmount 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden orderAmount;

        /// <summary>
        /// orderTime 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden orderTime;

        /// <summary>
        /// productName 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden productName;

        /// <summary>
        /// productNum 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden productNum;

        /// <summary>
        /// productId 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden productId;

        /// <summary>
        /// productDesc 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden productDesc;

        /// <summary>
        /// ext1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden ext1;

        /// <summary>
        /// ext2 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden ext2;

        /// <summary>
        /// signMsg 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden signMsg;

        /// <summary>
        /// payType 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden payType;

        /// <summary>
        /// fullAmountFlag 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden fullAmountFlag;

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
            //非法操作时重定向的URL地址
            string toUrl = "/Manage/Pay/99bill/PhonePay/Default.aspx";

            //接收第三方支付平台返回支付结果的页面地址，为绝对地址
            string receivePageUrl = UiCommon.StringConfig.WebSiteName + "/Manage/Pay/99bill/PhonePay/Receive.aspx";

            //商品名称（商户）
            string companyName = UiCommon.StringConfig.CompanyNameOfPay;

            //支付人
            if (Request.Form["txtUserName"] == null)
            {
                Response.Redirect(toUrl);
            }
            string userName = Request.Form["txtUserName"].ToString();

            //支付金额
            if (Request.Form["PayMoney"] == null)
            {
                Response.Redirect(toUrl);
            }
            string payMoney = Request.Form["PayMoney"].ToString().Trim();
            BLL.Member mem = new BLL.Member();
            int otherPayMoney = mem.UserTodayOtherPayMoney(userName.Trim());
            //是否超出今天充值限制额
            if (Convert.ToInt32(payMoney) > otherPayMoney)
            {
                Response.Write("<script>alert('您今天能充值金额数不能大于" + otherPayMoney + "。');location.href='" + toUrl + "';</script>");
                Response.End();
            }
            //支付类型 Web_RMBCost.PayType
            int payTypeLog = 1;

            //类型信息 Web_RMBCost.Typeinfo
            string typeInfoLog = "快钱神州行卡密支付";


            /**
             * @Description: 快钱神州行支付网关接口范例
             * @Copyright (c) 上海快钱信息服务有限公司
             * @version 2.0
             */

            //神州行网关账户号
            ///请与快钱技术联系索取
            merchantAcctId.Value = UiCommon.StringConfig.JJbill_SZX_Account;// "1001622591104";

            //设置神州行网关密钥
            ///区分大小写
            String key = UiCommon.StringConfig.JJbill_SZX_Key;// "84YB4FXGFKZ85975";


            //字符集.固定选择值。可为空。
            ///只能选择1、2、3、5
            ///1代表UTF-8; 2代表GBK; 3代表gb2312; 5 代表big5
            ///默认值为1
            inputCharset.Value = "1";

            //服务器接受支付结果的后台地址.与[pageUrl]不能同时为空。必须是绝对地址。
            ///快钱通过服务器连接的方式将交易结果发送到[bgUrl]对应的页面地址，在商户处理完成后输出的<result>如果为1，页面会转向到<redirecturl>对应的地址。
            ///如果快钱未接收到<redirecturl>对应的地址，快钱将把支付结果GET到[pageUrl]对应的页面。
            bgUrl.Value = receivePageUrl;

            //接受支付结果的页面地址.与[bgUrl]不能同时为空。必须是绝对地址。
            ///如果[bgUrl]为空，快钱将支付结果GET到[pageUrl]对应的地址。
            ///如果[bgUrl]不为空，并且[bgUrl]页面指定的<redirecturl>地址不为空，则转向到<redirecturl>对应的地址.
            pageUrl.Value = "";

            //网关版本.固定值
            ///快钱会根据版本号来调用对应的接口处理程序。
            ///本代码版本号固定为v2.0
            version.Value = "v2.0";

            //语言种类.固定选择值。
            ///只能选择1、2、3
            ///1代表中文；2代表英文
            ///默认值为1
            language.Value = "1";

            //签名类型.固定值
            ///1代表MD5签名
            ///当前版本固定为1
            signType.Value = "1";


            //支付人姓名
            ///可为中文或英文字符
            //payerName.Value="支付人";
            payerName.Value = userName;


            //支付人联系方式类型.固定选择值
            ///只能选择1
            ///1代表Email
            payerContactType.Value = "1";

            //支付人联系方式
            ///只能选择Email或手机号
            payerContact.Value = "";

            //商户订单号
            ///由字母、数字、或[-][_]组成
            orderId.Value = DateTime.Now.ToString("yyyyMMddHHmmssfffffff"); //DateTime.Now.ToString("yyyyMMddHHmmss");


            //订单金额
            ///以分为单位，必须是整型数字
            ///比方2，代表0.02元
            ///orderAmount.Value="100";
            double dblTemp = Double.Parse(payMoney);
            orderAmount.Value = Convert.ToString(dblTemp * 100);//元转换为分


            //订单提交时间
            ///14位数字。年[4位]月[2位]日[2位]时[2位]分[2位]秒[2位]
            ///如；20080101010101
            orderTime.Value = DateTime.Now.ToString("yyyyMMddHHmmss");

            //商品名称
            ///可为中文或英文字符
            //productName.Value="商品名称";
            productName.Value = companyName;

            //商品数量
            ///可为空，非空时必须为数字
            productNum.Value = "1";

            //商品代码
            ///可为字符或者数字
            productId.Value = "";

            //商品描述
            productDesc.Value = "";

            //扩展字段1
            ///在支付结束后原样返回给商户
            ext1.Value = userName;

            //扩展字段2
            ///在支付结束后原样返回给商户
            ext2.Value = "";


            //支付方式.固定选择值
            ///可选择00、41、42、52
            ///00 代表快钱默认支付方式，目前为神州行卡密支付和快钱账户支付；41 代表快钱账户支付；42 代表神州行卡密支付和快钱账户支付；52 代表神州行卡密支付
            payType.Value = "52";

            //全额支付标志
            ///只能选择数字 0 或 1
            ///0 代表非全额支付方式，支付完成后返回订单金额为商户提交的订单金额。如果预付费卡面额小于订单金额时，返回支付结果为失败；预付费卡面额大于或等于订单金额时，返回支付结果为成功；
            ///1 代表全额支付方式，支付完成后返回订单金额为用户预付费卡的面额。只要预付费卡销卡成功，返回支付结果都为成功。
            fullAmountFlag.Value = "0";



            //对所有含有中文字符的参数进行编码urlencode编码，并将编码后的结果全部转换成大写字母
            ///！注意：对于以下的五个参数，若不含中文字符的参数，请勿转换成大写字母（即无需调用“.ToUpper()”）。
            ///        否则，在返回页面接收到的返回参数将全部变为大写字母，这将可能导致数据库订单数据更新失败！！
            payerName.Value = System.Web.HttpUtility.UrlEncode(payerName.Value, Encoding.GetEncoding("UTF-8")).ToUpper();
            productName.Value = System.Web.HttpUtility.UrlEncode(productName.Value, Encoding.GetEncoding("UTF-8")).ToUpper();
            productDesc.Value = System.Web.HttpUtility.UrlEncode(productDesc.Value, Encoding.GetEncoding("UTF-8")).ToUpper();
            ext1.Value = System.Web.HttpUtility.UrlEncode(ext1.Value, Encoding.GetEncoding("UTF-8")).ToUpper();
            ext2.Value = System.Web.HttpUtility.UrlEncode(ext2.Value, Encoding.GetEncoding("UTF-8")).ToUpper();



            //生成加密签名串
            ///请务必按照如下顺序和规则组成加密串！
            String signMsgVal = "";
            signMsgVal = appendParam(signMsgVal, "inputCharset", inputCharset.Value);
            signMsgVal = appendParam(signMsgVal, "bgUrl", bgUrl.Value);
            signMsgVal = appendParam(signMsgVal, "pageUrl", pageUrl.Value);
            signMsgVal = appendParam(signMsgVal, "version", version.Value);
            signMsgVal = appendParam(signMsgVal, "language", language.Value);
            signMsgVal = appendParam(signMsgVal, "signType", signType.Value);
            signMsgVal = appendParam(signMsgVal, "merchantAcctId", merchantAcctId.Value);
            signMsgVal = appendParam(signMsgVal, "payerName", payerName.Value);
            signMsgVal = appendParam(signMsgVal, "payerContactType", payerContactType.Value);
            signMsgVal = appendParam(signMsgVal, "payerContact", payerContact.Value);
            signMsgVal = appendParam(signMsgVal, "orderId", orderId.Value);
            signMsgVal = appendParam(signMsgVal, "orderAmount", orderAmount.Value);
            signMsgVal = appendParam(signMsgVal, "payType", payType.Value);
            signMsgVal = appendParam(signMsgVal, "fullAmountFlag", fullAmountFlag.Value);
            signMsgVal = appendParam(signMsgVal, "orderTime", orderTime.Value);
            signMsgVal = appendParam(signMsgVal, "productName", productName.Value);
            signMsgVal = appendParam(signMsgVal, "productNum", productNum.Value);
            signMsgVal = appendParam(signMsgVal, "productId", productId.Value);
            signMsgVal = appendParam(signMsgVal, "productDesc", productDesc.Value);
            signMsgVal = appendParam(signMsgVal, "ext1", ext1.Value);
            signMsgVal = appendParam(signMsgVal, "ext2", ext2.Value);
            signMsgVal = appendParam(signMsgVal, "key", key);

            signMsg.Value = GetMD5(signMsgVal, "utf-8").ToUpper();


            //打印订单信息
            Lab_orderId.Text = orderId.Value;
            Lab_orderAmount.Text = payMoney;
            Lab_payerName.Text = userName;
            Lab_productName.Text = companyName;

            /*
            Response.Write("userName:" + userName + "<br>");
            Response.Write("payMoney:" + payMoney + "<br>");
            Response.Write("payTypeLog:" + payTypeLog + "<br>");
            Response.Write("typeInfoLog:" + typeInfoLog + "<br>");
            Response.Write("orderId:" + orderId.Value + "<br>");
            Response.End();
            */

            //支付成功前， 插入支付的订单日志
            new BLL.Member().Add3PayOrder(userName, Convert.ToInt32(payMoney), payTypeLog, typeInfoLog, orderId.Value);
        }

        //功能函数。将变量值不为空的参数组成字符串。开始
        String appendParam(String returnStr, String paramId, String paramValue)
        {
            if (returnStr != "")
            {

                if (paramValue != "")
                {

                    returnStr += "&" + paramId + "=" + paramValue;
                }

            }
            else
            {

                if (paramValue != "")
                {
                    returnStr = paramId + "=" + paramValue;
                }
            }

            return returnStr;
        }
        //功能函数。将变量值不为空的参数组成字符串。结束



        //功能函数。将字符串进行编码格式转换，并进行MD5加密，然后返回。开始
        private static string GetMD5(string dataStr, string codeType)
        {
            System.Security.Cryptography.MD5 md5 = new System.Security.Cryptography.MD5CryptoServiceProvider();
            byte[] t = md5.ComputeHash(System.Text.Encoding.GetEncoding(codeType).GetBytes(dataStr));
            System.Text.StringBuilder sb = new System.Text.StringBuilder(32);
            for (int i = 0; i < t.Length; i++)
            {
                sb.Append(t[i].ToString("x").PadLeft(2, '0'));
            }
            return sb.ToString();
        }
        //功能函数。将字符串进行编码格式转换，并进行MD5加密，然后返回。结束
    }

}
