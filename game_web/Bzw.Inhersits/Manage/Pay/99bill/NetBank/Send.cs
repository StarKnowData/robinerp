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
namespace Bzw.Inhersits.Manage.Pay._99bill.NetBank
{
    public partial class Manage_Pay_99bill_NetBank_Send : UiCommon.BasePage
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
        /// payType 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden payType;

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
        /// bankId 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden bankId;

        /// <summary>
        /// redoFlag 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden redoFlag;

        /// <summary>
        /// pid 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputHidden pid;

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
            string toUrl = "/Manage/Pay/99bill/NetBank/Default.aspx";

            //接收第三方支付平台返回支付结果的页面地址，为绝对地址
            string receivePageUrl = UiCommon.StringConfig.WebSiteName + "/Manage/Pay/99bill/NetBank/Receive.aspx";

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
            int payTypeLog = 2;

            //类型信息 Web_RMBCost.Typeinfo
            string typeInfoLog = "快钱网上银行转帐支付";


            /**
             * @Description: 快钱人民币支付网关接口范例
             * @Copyright (c) 上海快钱信息服务有限公司
             * @version 2.0
             */

            //人民币网关账户号
            ///请登录快钱系统获取用户编号，用户编号后加01即为人民币网关账户号。
            merchantAcctId.Value = UiCommon.StringConfig.JJbill_NetBank_Account;//"1001622591101";

            //人民币网关密钥
            ///区分大小写.请与快钱联系索取
            String key = UiCommon.StringConfig.JJbill_NetBank_Key;// "K65XTCHC2N72M4MS";


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
            ///只能选择00、10、11、12、13、14
            ///00：组合支付（网关支付页面显示快钱支持的各种支付方式，推荐使用）10：银行卡支付（网关支付页面只显示银行卡支付）.11：电话银行支付（网关支付页面只显示电话支付）.12：快钱账户支付（网关支付页面只显示快钱账户支付）.13：线下支付（网关支付页面只显示线下支付方式）.14：B2B支付（网关支付页面只显示B2B支付，但需要向快钱申请开通才能使用）
            payType.Value = "00";

            //银行代码
            ///实现直接跳转到银行页面去支付,只在payType=10时才需设置参数
            ///具体代码参见 接口文档银行代码列表
            bankId.Value = "";

            //同一订单禁止重复提交标志
            ///固定选择值： 1、0
            ///1代表同一订单号只允许提交1次；0表示同一订单号在没有支付成功的前提下可重复提交多次。默认为0建议实物购物车结算类商户采用0；虚拟产品类商户采用1
            redoFlag.Value = "1";

            //快钱的合作伙伴的账户号
            ///如未和快钱签订代理合作协议，不需要填写本参数
            pid.Value = "";


            //生成加密签名串
            ///请务必按照如下顺序和规则组成加密串！
            String signMsgVal = "";
            signMsgVal = appendParam(signMsgVal, "inputCharset", inputCharset.Value);
            signMsgVal = appendParam(signMsgVal, "pageUrl", pageUrl.Value);
            signMsgVal = appendParam(signMsgVal, "bgUrl", bgUrl.Value);
            signMsgVal = appendParam(signMsgVal, "version", version.Value);
            signMsgVal = appendParam(signMsgVal, "language", language.Value);
            signMsgVal = appendParam(signMsgVal, "signType", signType.Value);
            signMsgVal = appendParam(signMsgVal, "merchantAcctId", merchantAcctId.Value);
            signMsgVal = appendParam(signMsgVal, "payerName", payerName.Value);
            signMsgVal = appendParam(signMsgVal, "payerContactType", payerContactType.Value);
            signMsgVal = appendParam(signMsgVal, "payerContact", payerContact.Value);
            signMsgVal = appendParam(signMsgVal, "orderId", orderId.Value);
            signMsgVal = appendParam(signMsgVal, "orderAmount", orderAmount.Value);
            signMsgVal = appendParam(signMsgVal, "orderTime", orderTime.Value);
            signMsgVal = appendParam(signMsgVal, "productName", productName.Value);
            signMsgVal = appendParam(signMsgVal, "productNum", productNum.Value);
            signMsgVal = appendParam(signMsgVal, "productId", productId.Value);
            signMsgVal = appendParam(signMsgVal, "productDesc", productDesc.Value);
            signMsgVal = appendParam(signMsgVal, "ext1", ext1.Value);
            signMsgVal = appendParam(signMsgVal, "ext2", ext2.Value);
            signMsgVal = appendParam(signMsgVal, "payType", payType.Value);
            signMsgVal = appendParam(signMsgVal, "bankId", bankId.Value);
            signMsgVal = appendParam(signMsgVal, "redoFlag", redoFlag.Value);
            signMsgVal = appendParam(signMsgVal, "pid", pid.Value);
            signMsgVal = appendParam(signMsgVal, "key", key);
            signMsg.Value = FormsAuthentication.HashPasswordForStoringInConfigFile(signMsgVal, "MD5").ToUpper();


            //打印订单信息
            Lab_orderId.Text = orderId.Value;
            Lab_orderAmount.Text = payMoney;
            Lab_payerName.Text = payerName.Value;
            Lab_productName.Text = productName.Value;

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
    }
}
