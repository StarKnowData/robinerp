using System;
using System.Collections.Generic;
using System.Text;

namespace Bzw.Inhersits.Manage.Pay.IPS
{
  public partial  class Manage_Pay_IPS_CheckOrder:UiCommon.BasePage
    {
      protected void Page_Load(object sender, EventArgs e)
      {
          string billno = Utility.Common.GetStringOfUrl("billno"); //订单编号

          string mercode = Utility.Common.GetStringOfUrl("mercode");//商户编号

          string amount = Utility.Common.GetStringOfUrl("amount");  //订单金额

          string date = Utility.Common.GetStringOfUrl("date"); //订单日期

          string succ = Utility.Common.GetStringOfUrl("succ"); //成功标志

          string ipsbillno = Utility.Common.GetStringOfUrl("ipsbillno"); //IPS订单编号

          string currency_Type = Utility.Common.GetStringOfUrl("Currency_type");  //币种

          string signature = Utility.Common.GetStringOfUrl("signature").ToLower(); //MD5签名 

          string msg = Utility.Common.GetStringOfUrl("msg");//ips返回订单信息

          string attach = Utility.Common.GetStringOfUrl("attach");//商户数据包

          string retencodetype = Utility.Common.GetStringOfUrl("retencodetype");//数字签名方式

          string ipsbanktime = Utility.Common.GetStringOfUrl("ipsbanktime");//银行返回时间

          string signatureVal = Utility.Common.md5("billno" + billno + "currencytype" + currency_Type + "amount" + amount + "date" + date + "succ" + succ + "ipsbillno" + ipsbillno + "retencodetype" + retencodetype + UiCommon.StringConfig.IPS_Letter).ToLower();
          if (succ == "Y")
          {
              if (signature.Equals(signatureVal.ToLower()))
              {
                  BLL.Member mem = new BLL.Member();
                  bool fl = mem.IsPaySuccess(billno);
                  if (fl)
                  {
                      Response.Write("ipscheckok");
                      Response.End();
                  }
                  else
                  {
                      mem.Update3PayOrder((int)(float.Parse(amount)), billno);
                      Response.Write("ipscheckok");
                      Response.End();
                  }
              }
          }
      }
    }
}
