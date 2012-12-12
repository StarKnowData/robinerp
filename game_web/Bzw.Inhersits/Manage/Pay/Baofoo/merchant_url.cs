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
using Utility;
using System.Data.SqlClient;

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

                    #region [add] jeffery

                    int pos = additionalInfo.IndexOf("!@#");
                    string username = additionalInfo.Substring(0, pos);
                    int couponNum =
                        Convert.ToInt32(
                        additionalInfo.Substring(pos + 1)
                        );
                    string strsql =
                        "select UserID from TUsers where UserName=@username";

                    DataTable dt =
                        SqlHelper.ExecuteDataset(CommandType.Text,
                        strsql,
                        new SqlParameter[]
                                {
                                    new SqlParameter("@username",username)
                                }
                        ).Tables[0];

                    int userid = Convert.ToInt32(dt.Rows[0]["UserID"]);

                    strsql = "insert into TCoupon(UserID,CouponNum,RechargeType,CreateTime)values(@userid,@coupon,@rechargeType,@createTime)";
                    int num =
                        SqlHelper.ExecuteNonQuery
                        (CommandType.Text,
                        strsql,
                        new SqlParameter[]
                                {
                                    new SqlParameter("@userid",userid),
                                    new SqlParameter("@coupon",couponNum),
                                    new SqlParameter("@rechargeType",5),
                                    new SqlParameter("@createTime",DateTime.Now) 
                                });


                    if (num != 1)
                    {
                        Response.Write("<script>alert('充值成功，但赠送奖劵失败！')</script>");
                    }


                    #endregion

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
