using System;
using System.Collections.Generic;
using System.Text;
using BLL;
using System.IO;

namespace Bzw.Inhersits.Manage.Pay.KF
{
    public partial class Manage_Pay_KF_Result : UiCommon.BasePage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            string UserId =Utility.Common.GetStringOfUrl( Request["P_UserId"]);
            string OrderId = Utility.Common.GetStringOfUrl(Request["P_OrderId"]);
            string CardId = Utility.Common.GetStringOfUrl(Request["P_CardId"]);
            string CardPass = Utility.Common.GetStringOfUrl(Request["P_CardPass"]);
            string FaceValue = Utility.Common.GetStringOfUrl(Request["P_FaceValue"]);
            string ChannelId = Utility.Common.GetStringOfUrl(Request["P_ChannelId"]);

            string subject = Utility.Common.GetStringOfUrl(Request["P_Subject"]);
            string description = Utility.Common.GetStringOfUrl(Request["P_Description"]);
            string price = Utility.Common.GetStringOfUrl(Request["P_Price"]);
            string quantity = Utility.Common.GetStringOfUrl(Request["P_Quantity"]);
            string notic = Utility.Common.GetStringOfUrl(Request["P_Notic"]);
            string ErrCode = Utility.Common.GetStringOfUrl(Request["P_ErrCode"]);
            string PostKey = Utility.Common.GetStringOfUrl(Request["P_PostKey"]);
            string payMoney = Utility.Common.GetStringOfUrl(Request["P_PayMoney"]);

            string SalfStr =UiCommon.StringConfig.KFPayKey;
            string preEncodeStr = UserId + "|" + OrderId + "|" + CardId + "|" + CardPass + "|" + FaceValue + "|" + ChannelId + "|" + SalfStr;

            string encodeStr = Utility.Common.md5(preEncodeStr);

          //   Response.Write(preEncodeStr + "<br>" + encodeStr+"<br>");//调试语句

             Response.Write("errCode=0");
             //string FilePath = Server.MapPath("/test/weather.txt");
             //if (!File.Exists(FilePath))
             //{
             //    FileStream fs = File.Create(FilePath);
             //    fs.Close();
             //}
             ////写入文本  
             //StreamWriter sr = new StreamWriter(Server.MapPath("/test/weather.txt"), false, System.Text.Encoding.Default);
             //try
             //{
             //    string str = "P_UserId:" + UserId + "P_OrderId:" + OrderId + "P_CardId:" 
             //        + CardId + "P_CardPass:" + CardPass + "P_FaceValue:" + FaceValue
             //        + "P_ChannelId:" + ChannelId + "P_Subject:" + subject
             //        + "P_Description:" + description + "P_Price:" + price
             //        + "P_ErrCode:" + ErrCode + "P_PostKey:" + PostKey
             //        + "P_PayMoney:" + payMoney;
             //    sr.Write(str+"<br/>"+preEncodeStr + "<br/>" + encodeStr + "<br/>");
             //    sr.Close();
                 
             //}
             //catch
             //{
                 
             //}  
            if (PostKey.ToUpper().CompareTo(encodeStr.ToUpper()) == 0)//表示数据合法
            {

                if (int.Parse(ErrCode) == 0)//说明是充值成功了的
                {
                    //这里进行订单更新
                    Member mem = new Member();
                    if (!mem.IsPaySuccess(OrderId))
                    {
                        mem.Update3PayOrder((int)(float.Parse(FaceValue)), OrderId);
                    }
                     
                }
                else
                {
                 //   Response.Write("-Err");
                }
            }
            else
            {
                
               // Response.Write("-数据不合法");
            }
        }
        
    }
}
