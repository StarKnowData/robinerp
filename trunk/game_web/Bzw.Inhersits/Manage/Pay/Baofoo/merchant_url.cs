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
using System.Web.Configuration;

namespace Bzw.Inhersits
{
    public partial class Manage_Pay_Baofoo_merchant_url : UiCommon.BasePage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            string MerchantID = Request.Params["MerchantID"];//商户号
            string TransID = Request.Params["TransID"];//商户流水号
            string Result = Request.Params["Result"];//支付结果(1:成功,0:失败)
            string resultDesc = Request.Params["resultDesc"];//支付结果描述
            string factMoney = Request.Params["factMoney"];//实际成交金额
            string additionalInfo = Request.Params["additionalInfo"];//订单附加消息
            string SuccTime = Request.Params["SuccTime"];//交易成功时间
            string Md5Sign = Request.Params["Md5Sign"].ToLower();//md5签名

            string _Md5Key = ConfigurationManager.AppSettings["baofoo_key"];
            string _WaitSign = MerchantID + TransID + Result + resultDesc + factMoney + additionalInfo + SuccTime + _Md5Key;
            if (Result == "1")
            {
                if (Md5Sign.ToLower() == Helper.Md5Encrypt(_WaitSign).ToLower())
                {
                    //开始下面的操作，处理订单
                    BLL.Member member = new BLL.Member();
                    if (!member.IsPaySuccess(TransID)) //防止重复刷新页面而带来的问题
                    {

                        //更新订单信息为完成状态
                        if (TransID.ToLower().Contains("ka"))
                            member.Update3PayOrder2((int)(float.Parse(factMoney)) / 100, TransID);
                        else
                            member.Update3PayOrder((int)(float.Parse(factMoney)) / 100, TransID);
                    }
                     
                    //md5校验成功，输出OK
                    Response.Write("OK");
                }
            }
            else
            {
                Response.Write("Md5CheckFail");
            }
        }

    }
}
