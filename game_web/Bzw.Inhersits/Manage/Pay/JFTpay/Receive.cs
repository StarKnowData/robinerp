using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Text.RegularExpressions;
using Bzw.Data;
using BLL;


namespace Bzw.Inhersits
{
    public partial class Manage_Pay_JFTpay_Receive : UiCommon.BasePage 
    {

        protected void Page_Load(object sender, EventArgs e)
        {
            String key = UiCommon.StringConfig.JFTpay_MemberKey; //配置文件密钥


            //返回参数
            String orderid = Request.QueryString["orderid"];//返回订单号
            String opstate = Request.QueryString["opstate"];//返回处理结果
            String ovalue = Request.QueryString["ovalue"];//返回充值金额
            String sign = Request.QueryString["sign"];//返回加密标记
            String Reply = Request.QueryString["Reply"];//同步发送：1代表同步发送，2代表异步发送
            String kaorderID = Request.QueryString["ekaorderid"];
            String time = Request.QueryString["ekatime"];//亿卡处理时间。


            //组织参数
            String param = String.Format("orderid={0}&opstate={1}&ovalue={2}{3}", orderid, opstate, ovalue, key);


            //比对参数是否有效
            if (sign.Equals(FormsAuthentication.HashPasswordForStoringInConfigFile(param, "MD5").ToLower()))
            {
                //执行操作方法
                if (opstate.Equals("0"))
                {
                    Member mem = new Member();

                    if (Reply == "1")
                    {
                        Response.Write("opstate=0");


                        //操作流程成功的情况
                        //注：不能打印其他的字符，否则不会同步
                        if (!mem.IsPaySuccess(orderid)) //防止重复刷新页面而带来的问题
                        {

                            //更新订单信息为完成状态
                            if (orderid.ToLower().Contains("ka"))
                                mem.Update3PayOrder2((int)(float.Parse(ovalue)), orderid);
                            else
                                mem.Update3PayOrder((int)(float.Parse(ovalue)), orderid);


                        
                        }

                    }
                    else if (Reply == "2")
                    {

                        //防止重复刷新页面而带来的问题
                        if (!mem.IsPaySuccess(orderid))
                        {
                            if (orderid.ToLower().Contains("ka"))
                                mem.Update3PayOrder2((int)(float.Parse(ovalue)), orderid);
                            else
                                mem.Update3PayOrder((int)(float.Parse(ovalue)), orderid);

                        }
                        //返回到成功页面
                        Response.Redirect("NotityReceive.aspx?orderid=" + orderid + "&opstate=" + opstate);

                    }

                }
                if (opstate.Equals("-1"))
                {
                    //请求参数无效
                    Response.Write("请求参数无效");
                }
                if (opstate.Equals("-2"))
                {
                    //交易签名无效
                    Response.Write("签名错误");
                }
            }
        }



    

    }
}
