using System;
using System.Collections.Generic;
using System.Text;
using System.Configuration;
using BLL;
using System.IO;

namespace Bzw.Inhersits.Manage.Pay.KF
{
    public partial class Manage_Pay_KF_Return : UiCommon.BasePage
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

            string SalfStr = UiCommon.StringConfig.KFPayKey;
            string preEncodeStr = UserId + "|" + OrderId + "|" + CardId + "|" + CardPass + "|" + FaceValue + "|" + ChannelId + "|" + SalfStr;

            string encodeStr = Utility.Common.md5(preEncodeStr);

           //  Response.Write(preEncodeStr + "<br>" + encodeStr+"<br>");//调试语句
            PayOrderID = OrderId;

            PayMoney = FaceValue;
            //string FilePath = Server.MapPath("/test/weather.txt");
            //if (!File.Exists(FilePath))
            //{
            //    FileStream fs = File.Create(FilePath);
            //    fs.Close();
            //}
            ////写入文本  
            //StreamWriter sr = new StreamWriter(Server.MapPath("/test/weather1.txt"), false, System.Text.Encoding.Default);
            //try
            //{
            //    string str = "P_UserId:" + UserId + "P_OrderId:" + OrderId + "P_CardId:"
            //        + CardId + "P_CardPass:" + CardPass + "P_FaceValue:" + FaceValue
            //        + "P_ChannelId:" + ChannelId + "P_Subject:" + subject
            //        + "P_Description:" + description + "P_Price:" + price
            //        + "P_ErrCode:" + ErrCode + "P_PostKey:" + PostKey
            //        + "P_PayMoney:" + payMoney;
            //    sr.Write(str + "<br/>" + preEncodeStr + "<br/>" + encodeStr + "<br/>");
            //    sr.Close();

            //}
            //catch
            //{

            //}  
            if (PostKey.ToUpper().CompareTo(encodeStr.ToUpper()) == 0)
            {
              //  Response.Write("errCode=0");//表示数据合法
                if (int.Parse(ErrCode) == 0)//说明是充值成功了的
                {
                    //这里进行订单更新

                    PayResult = "恭喜您，充值成功！";
                    Member mem = new Member();
                    if (!mem.IsPaySuccess(OrderId))
                    {
                        mem.Update3PayOrder((int)(float.Parse(PayMoney)), PayOrderID);
                    }
                }
                else
                {
                    PayResult = "充值失败，请不要恶意删改数据";
                }
            }
            else
            {
                //交易失败
                switch(encodeStr){
                    case "101": PayResult = "商户ID为空"; break;
                    case "102": PayResult = "卡号不合法"; break;
                    case "103": PayResult = "卡密不合法"; break;
                    case "104": PayResult = "卡号太长"; break;
                    case "105": PayResult = "卡密太长"; break;
                    case "106": PayResult = "面值数据不合法"; break;
                    case "107": PayResult = "充值类型错误"; break;
                    case "108": PayResult = "游戏用户名过长"; break;
                    case "109": PayResult = "用户不存在"; break;
                    case "110": PayResult = "加密串postKey错误"; break;
                    case "111": PayResult = "该卡号已经被使用过"; break;
                    case "112": PayResult = "卡号类型不存在"; break;
                    case "113": PayResult = "未开通此通道或者业务"; break;
                    case "114": PayResult = "系统配置错误"; break;
                    case "115": PayResult = "卡号卡密或者面值不相符合"; break;
                    case "116": PayResult = "未知错误"; break;
                    case "117": PayResult = "未知错误"; break;
                    case "118": PayResult = "商户订单号为空"; break;
                    case "119": PayResult = "商户订单号太长"; break;
                    case "120": PayResult = "充值金额不合法"; break;
                    case "121": PayResult = "产品名称太长"; break;
                    case "122": PayResult = "产品描述文字太多"; break;
                    case "123": PayResult = "产品单价不是数字"; break;
                    case "124": PayResult = "用户自定义信息文字太多"; break;
                    case "125": PayResult = "notify_url太长"; break;
                    case "126": PayResult = "result_url太长"; break;
                    default: PayResult = "未知错误"; break;
                }
            }
        }
        
    }
}
