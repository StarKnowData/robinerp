using System;
using System.Collections.Generic;
using System.Text;
using BCST.Common;

namespace Bzw.Inhersits.Manage.Pay.KF
{
      public partial class Manage_Pay_KF_Send : UiCommon.BasePage
    {
          protected void Page_Load(object sender, EventArgs e)
          {
              string errorUrl = "/Manage/Pay/KF/Default.aspx"; //出错跳转地址
              BLL.Member mem = new BLL.Member();

              string txtUserName = Utility.Common.GetStringOfForm("txtUserName"); //用户名

              if (!mem.ExistName(txtUserName.Trim()))
              {
                  Response.Write("<script>alert('找不到您要充值的用户帐号，请检查输入是否有误');location.href='" + errorUrl + "';</script>");
                  Response.End();
              }
              
              //支付金额
              string payMoney = Utility.Common.GetStringOfForm("PayMoney");
              if (string.IsNullOrEmpty(payMoney) || !CommonManager.String.IsInteger(payMoney) || int.Parse(payMoney) <= 0)
              {
                  CommonManager.Web.RegJs(this, "alert('金额只能输入大于0的整数。');history.back();", false);
                  return;
              }
              int otherPayMoney = mem.UserTodayOtherPayMoney(txtUserName.Trim());
              //是否超出今天充值限制额
              if (Convert.ToInt32(payMoney) > otherPayMoney)
              {
                  Response.Write("<script>alert('您今天能充值金额数不能大于" + otherPayMoney + "。');location.href='" + errorUrl + "';</script>");
                  Response.End();
              }
              //充值类型
              string payType = Utility.Common.GetStringOfForm("channelId");
              string P_CardId = string.Empty;
              string P_CardPass = string.Empty;
              if (payType != "1" && payType != "2" && payType != "3")
              {
                  P_CardId = Utility.Common.GetStringOfForm("CardNo");
                  P_CardPass = Utility.Common.GetStringOfForm("CardPwd");
              }
              else
              { 
              
              }
              int payTypeLog = 8;
              //商户定单编号
              string P_OrderId = DateTime.Now.ToString("yyyyMMddHHmmssfffffff"); 
              //支付成功前， 插入支付的订单日志 
              mem.Add3PayOrder(txtUserName, Convert.ToInt32(payMoney), payTypeLog, "花旗充值", P_OrderId);
              //商户编号
              string P_UserId = UiCommon.StringConfig.KFPayID;
              //面值
              string P_FaceValue = payMoney + ".00";
              //充值类型
              string P_ChannelId = payType;
              //产品名称
              string P_Subject = "";
              //产品价格
              string P_Price = payMoney + ".00";
             
               //产品数量
              string P_Quantity ="1";
              //产品描述
              string P_Description = "";
              //用户附加信息
              string P_Notic = "";
              //充值状态通知地址
              string P_Result_URL = UiCommon.StringConfig.WebSiteName+"/Manage/Pay/KF/Result.aspx";
              //充值后网页跳转地址
              string P_Notify_URL = UiCommon.StringConfig.WebSiteName + "/Manage/Pay/KF/Return.aspx";
              //密钥
              string SalfStr = UiCommon.StringConfig.KFPayKey;
              //签名认证
              string preEncodeStr = P_UserId + "|" + P_OrderId + "|" + P_CardId + "|" + P_CardPass + "|" + P_FaceValue + "|" + P_ChannelId + "|" + SalfStr;
              string P_PostKey = Utility.Common.md5(preEncodeStr);
              //Response.Write(P_PostKey+"</br>"+Utility.Common.md5(preEncodeStr).ToUpper());
              //Response.End();
              //接口url
              string url = UiCommon.StringConfig.KFNotifyURL+"P_UserId="+P_UserId+"&P_OrderId="+P_OrderId+"&P_CardId="+P_CardId+"&P_CardPass="
                  +P_CardPass+"&P_FaceValue="+P_FaceValue+"&P_ChannelId="+P_ChannelId+"&P_Subject="+P_Subject+"&P_Price="
                  +P_Price+"&P_Quantity="+P_Quantity+"&P_Description="+P_Description+"&P_Notic="+P_Notic+"&P_PostKey="+P_PostKey
                  +"&P_Result_url="+P_Result_URL+"&P_Notify_URL="+P_Notify_URL;
              
             Response.Redirect(url);
          }
        
    }
}
