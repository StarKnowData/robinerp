using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using System.Data.SqlClient;
using BLL;
using Utility;

namespace Bzw.Inhersits.Manage.Pay.IPS
{
    public partial class Manage_Pay_IPS_OrderReturn : UiCommon.BasePage
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
            string billno = Utility.Common.GetStringOfUrl("billno"); //订单编号

            string amount = Utility.Common.GetStringOfUrl("amount");  //订单金额

            string date = Utility.Common.GetStringOfUrl("date"); //订单日期

            string succ = Utility.Common.GetStringOfUrl("succ"); //成功标志

            string ipsbillno = Utility.Common.GetStringOfUrl("ipsbillno"); //IPS订单编号

            string currency_Type = Utility.Common.GetStringOfUrl("Currency_type");  //币种

            string signature = Utility.Common.GetStringOfUrl("signature").ToLower(); //MD5签名

            string retencodetype = Utility.Common.GetStringOfUrl("retencodetype");//交易返回签名方式

            // [add] jeffery
            //string strAttach = Utility.Common.GetStringOfUrl("attach");
            // ---end

            if (string.IsNullOrEmpty(billno) || string.IsNullOrEmpty(amount) || string.IsNullOrEmpty(date) ||
                string.IsNullOrEmpty(succ) || string.IsNullOrEmpty(ipsbillno) || string.IsNullOrEmpty(currency_Type) || string.IsNullOrEmpty(signature))
            {
                Server.Transfer("Default.aspx");
            }

            PayOrderID = billno;

            PayMoney = amount;



            if (succ.Equals("Y"))
            {
                //交易成功
                PayResult = "恭喜您，充值成功！";
                if (currency_Type == null || currency_Type == "")
                {
                    currency_Type = "RMB";
                }
                string signatureVal = Utility.Common.md5("billno" + billno + "currencytype" + currency_Type + "amount" + amount + "date" + date + "succ" + succ + "ipsbillno" + ipsbillno + "retencodetype" + retencodetype + UiCommon.StringConfig.IPS_Letter).ToLower();

                if (signature.Equals(signatureVal.ToLower()))
                {
                    Member mem = new Member();
                    if (!mem.IsPaySuccess(billno))
                    {
                        mem.Update3PayOrder((int)(float.Parse(PayMoney)), PayOrderID);
                    }

                    #region [add] jeffery

                    //int pos = strAttach.IndexOf("!@#");
                    //string username = strAttach.Substring(0, pos);
                    //int couponNum =
                    //    Convert.ToInt32(
                    //    strAttach.Substring(pos + 1)
                    //    );
                    //string strsql =
                    //    "select UserID from TUsers where UserName=@username";

                    //DataTable dt =
                    //    SqlHelper.ExecuteDataset(CommandType.Text,
                    //    strsql,
                    //    new SqlParameter[]
                    //            {
                    //                new SqlParameter("@username",username)
                    //            }
                    //    ).Tables[0];

                    //int userid = Convert.ToInt32(dt.Rows[0]["UserID"]);


                    //strsql = "insert into TCoupon(UserID,CouponNum,RechargeType,CreateTime)values(@userid,@coupon,@rechargeType,@createTime)";
                    //int num =
                    //    SqlHelper.ExecuteNonQuery
                    //    (CommandType.Text,
                    //    strsql,
                    //    new SqlParameter[]
                    //            {
                    //                new SqlParameter("@userid",userid),
                    //                new SqlParameter("@coupon",couponNum),
                    //                new SqlParameter("@rechargeType",2),
                    //                new SqlParameter("@createTime",DateTime.Now) 
                    //            });

                    //if (num != 1)
                    //{
                    //    Response.Write("<script>alert('充值成功，但赠送奖劵失败！')</script>");
                    //}

                    #endregion
                }
                else
                {
                    PayResult = "充值失败，请不要恶意删改数据";
                }


            }
            else
            {
                //交易失败
                PayResult = "充值失败，请稍后再试！";
            }

        }


    }
}
