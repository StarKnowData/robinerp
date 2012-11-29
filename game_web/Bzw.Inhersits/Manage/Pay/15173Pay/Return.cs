using System;
using System.Collections.Generic;
using System.Text;
using Gateway;

namespace Bzw.Inhersits.Manage.Pay._15173Pay
{
  public partial  class Manage_Pay_15173Pay_Return:UiCommon.BasePage
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
        /// webtop1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webtop1;

        /// <summary>
        /// form2 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlForm form2;

        /// <summary>
        /// Lab_msg 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Literal Lab_msg;

        /// <summary>
        /// Control1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl Control1;
        /// <summary>
        /// created by sunzhizhi 2006.5.21,sunzhizhi@msn.com。
        /// </summary>
        /// 

        public string PayResult = string.Empty;
        public string PayMoney = string.Empty;
        public string PayOrderID = string.Empty;

        protected void Page_Load(object sender, EventArgs e)
        {
            Pay15173 pays = new Pay15173();
            //商户ID
            pays.Bargainor_id = UiCommon.StringConfig.Pay15173ID;

            //商户密钥
            pays.Key = UiCommon.StringConfig.Pay15173Key;

            string errmsg = string.Empty;
            if (!pays.GetPayValueFromUrl(Request.QueryString, out errmsg))	//返回的参数不合法
            {
                PayResult = "支付失败，";
                PayResult += errmsg;							//返回参数不合法的错误信息
                return;
            }
            else
            {
                string orderid = pays.Sp_billno.ToString();
                string payAmount = pays.Total_fee.ToString();
                PayResult = pays.PayResultStr;					//返回支付状态	
                if (pays.PayResult == Pay15173.PAYERROR)
                {
                    PayResult += pays.PayErrMsg;				//支付失败时返回的错误信息
                    PayOrderID = orderid;
                    PayMoney = payAmount + " 元";
                    return;
                }
                if (pays.PayResult == Pay15173.PAYOK)				//支付成功，更新订单
                {
                    BLL.Member member = new BLL.Member();
                    if (!member.IsPaySuccess(orderid)) //防止重复刷新页面而带来的问题
                    {
                        //更新订单状态为完成
                        //member.Update3PayOrder( string.Empty, (int)( float.Parse( payAmount ) ), Orderid );
                        member.Update3PayOrder((int)(float.Parse(payAmount)), orderid);
                    }
                    PayResult = "恭喜您，支付成功！";
                    PayOrderID = orderid;
                    PayMoney = payAmount + " 元";

                }
            }
        }


        
    }
}
