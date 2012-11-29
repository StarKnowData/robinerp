using System;
using System.Data;
using System.Configuration;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using System.Text;
using System.Security.Cryptography;
using System.Collections.Specialized;
using System.IO;
using System.Data.SqlClient;
using System.Data.OleDb;
using System.Net;

namespace Bzw.Inhersits.Manage.Pay.Alipay
{
    public partial class Manage_Pay_Alipay_Return : UiCommon.BasePage
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
            //***************************************************************     
            string alipayNotifyURL = UiCommon.StringConfig.AlipayNotifyURL;
            //partner 的对应交易安全校验码（必须填写）
            string key = UiCommon.StringConfig.AlipayKey;
            string _input_charset = "utf-8";
            //partner合作伙伴id（必须填写）
            string partner = UiCommon.StringConfig.AlipayPartnerID;

            alipayNotifyURL = alipayNotifyURL + "service=notify_verify" + "&partner=" + partner + "&notify_id=" + Request.QueryString["notify_id"];

            //获取支付宝ATN返回结果，true是正确的订单信息，false 是无效的
            string responseTxt = Get_Http(alipayNotifyURL, 120000);
            int i;
            NameValueCollection coll;
            //Load Form variables into NameValueCollection variable.
            coll = Request.QueryString;

            // Get names of all forms into a string array.
            String[] requestarr = coll.AllKeys;


            //进行排序；
            string[] Sortedstr = BubbleSort(requestarr);

            //for (i = 0; i < Sortedstr.Length; i++)
            //{ 
            //   Response.Write("Form: " + Sortedstr[i] + "=" + Request.QueryString[Sortedstr[i]] + "<br>");
            //}

            //构造待md5摘要字符串 ；

            StringBuilder prestr = new StringBuilder();

            for (i = 0; i < Sortedstr.Length; i++)
            {
                if (Request.Form[Sortedstr[i]] != "" && Sortedstr[i] != "sign" && Sortedstr[i] != "sign_type")
                {
                    if (i == Sortedstr.Length - 1)
                    {
                        prestr.Append(Sortedstr[i] + "=" + Request.QueryString[Sortedstr[i]]);
                    }
                    else
                    {
                        prestr.Append(Sortedstr[i] + "=" + Request.QueryString[Sortedstr[i]] + "&");

                    }
                }
            }

            prestr.Append(key);
            //**********************************************************************
            //生成Md5摘要；
            // string mysign = GetMD5(prestr.ToString(), _input_charset);
            string mysign = GetMD5(prestr.ToString(), _input_charset);
            string sign = Request.QueryString["sign"];
            string trade_status = Request.QueryString["trade_status"];

            //Response.Write(prestr.ToString());  //打印返回通知消息，接收到的


            //订单流水号
            string Orderid = Request.QueryString["out_trade_no"].Trim();
            //支付金额
            string payAmount = Request.QueryString["total_fee"].Trim();

            if (mysign == sign && responseTxt == "true")   //验证支付发过来的消息，签名是否正确
            {

                //更新自己数据库的订单语句，请自己填写一下**************************************************


                BLL.Member member = new BLL.Member();
                if (!member.IsPaySuccess(Orderid)) //防止重复刷新页面而带来的问题
                {
                    //更新订单状态为完成
                    //member.Update3PayOrder( string.Empty, (int)( float.Parse( payAmount ) ), Orderid );
                    member.Update3PayOrder((int)(float.Parse(payAmount)), Orderid);
                }
                PayResult = "恭喜您，支付成功！";
                PayOrderID = Orderid;
                PayMoney = payAmount + " 元";

                //Lab_msg.Text = "恭喜您，充值成功，订单号为" + Orderid + "，充值金额为" + payAmount + "元！<br>";

                Response.Write("success");     //返回给支付宝消息，成功（不用返回给支付宝）
                //**************************************************************************
                //打印出接收通知。计算结果
                //Response.Write("------------------------------------------");
                //Response.Write("<br>Result:responseTxt=" + responseTxt);
                //Response.Write("<br>Result:mysign=" + mysign);
                //Response.Write("<br>Result:sign=" + sign);

            }
            else
            {
                PayResult = "抱歉，支付失败！";
                PayOrderID = Orderid;
                PayMoney = payAmount + " 元，如果您确认钱已支付，请及时向我们反馈此问题！";
                // Lab_msg.Text = "对不起，充值失败，订单号为" + Orderid + "，充值金额为" + payAmount + "元，如果您确认钱已支付，请及时向我们反馈此问题！<br>";

                //**************************************************************************
                //打印出接收通知。计算结果
                //Response.Write("------------------------------------------");
                //Response.Write("<br>Result:responseTxt=" + responseTxt);
                //Response.Write("<br>Result:mysign=" + mysign);
                //Response.Write("<br>Result:sign=" + sign);
            }

        }

        public static string GetMD5(string s, string _input_charset)
        {

            /// <summary>
            /// 与ASP兼容的MD5加密算法
            /// </summary>

            MD5 md5 = new MD5CryptoServiceProvider();
            byte[] t = md5.ComputeHash(Encoding.GetEncoding(_input_charset).GetBytes(s));
            StringBuilder sb = new StringBuilder(32);
            for (int i = 0; i < t.Length; i++)
            {
                sb.Append(t[i].ToString("x").PadLeft(2, '0'));
            }
            return sb.ToString();
        }

        public static string[] BubbleSort(string[] r)
        {
            /// <summary>
            /// 冒泡排序法
            /// </summary>

            int i, j; //交换标志 
            string temp;

            bool exchange;

            for (i = 0; i < r.Length; i++) //最多做R.Length-1趟排序 
            {
                exchange = false; //本趟排序开始前，交换标志应为假

                for (j = r.Length - 2; j >= i; j--)
                {
                    if (System.String.CompareOrdinal(r[j + 1], r[j]) < 0)　//交换条件
                    {
                        temp = r[j + 1];
                        r[j + 1] = r[j];
                        r[j] = temp;

                        exchange = true; //发生了交换，故将交换标志置为真 
                    }
                }

                if (!exchange) //本趟排序未发生交换，提前终止算法 
                {
                    break;
                }

            }
            return r;
        }


        //获取远程服务器ATN结果
        public String Get_Http(String a_strUrl, int timeout)
        {
            string strResult;
            try
            {

                HttpWebRequest myReq = (HttpWebRequest)HttpWebRequest.Create(a_strUrl);
                myReq.Timeout = timeout;
                HttpWebResponse HttpWResp = (HttpWebResponse)myReq.GetResponse();
                Stream myStream = HttpWResp.GetResponseStream();
                StreamReader sr = new StreamReader(myStream, Encoding.Default);
                StringBuilder strBuilder = new StringBuilder();
                while (-1 != sr.Peek())
                {
                    strBuilder.Append(sr.ReadLine());
                }

                strResult = strBuilder.ToString();
            }
            catch (Exception exp)
            {

                strResult = "错误：" + exp.Message;
            }

            return strResult;
        }
    }
}
