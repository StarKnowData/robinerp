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
using BLL;

namespace Bzw.Inhersits 
{
    public partial class Manage_Pay_Baofoo_return_url : UiCommon.BasePage
    {
        /// <summary>
        /// Head1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlHead Head1;

        /// <summary>
        /// webtop1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webtop1;

        /// <summary>
        /// webuserlogin1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webuserlogin1;


        /// <summary>
        /// Form1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlForm Form1;

        /// <summary>
        /// lblBillon 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Literal lblBillon;

        /// <summary>
        /// lblAmount 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Literal lblAmount;

        /// <summary>
        /// lblWalletMoney 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Literal lblWalletMoney;

        /// <summary>
        /// lblMsg 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Literal lblMsg;


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

            //MerchantID=SDF&TransID=234&Result=212&resultDesc=1&factMoney=20&additionalInfo=sdsfd&Md5Sign=323423

            lblBillon.Text = TransID;
            lblAmount.Text = (Convert.ToInt32(factMoney) / 100).ToString();

            if (Result == "1")
            {
                if (Md5Sign.ToLower() == Helper.Md5Encrypt(_WaitSign).ToLower())
                {

                    //交易成功
                    lblMsg.Text = "恭喜您，充值成功！";      
                    //更新订单
                    Member mem = new Member();
                    if (!mem.IsPaySuccess(TransID))
                    {
                        //更新订单信息为完成状态
                        if (TransID.ToLower().Contains("ka"))
                            mem.Update3PayOrder2((int)(float.Parse(factMoney))/100, TransID);
                        else
                            mem.Update3PayOrder((int)(float.Parse(factMoney))/100, TransID);


                    }
                }
                else
                {
                    lblMsg.Text = "充值失败，请稍后再试！";
                }
            }
            else
            {
                //交易失败
                lblMsg.Text = "充值失败，原因：" + resultDesc + "。请稍后再试！";
            }
        }
   

    }
}
