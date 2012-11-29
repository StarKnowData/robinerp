using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using Bzw.Data;
using BCST.Common;

 
    public partial class Admin_Games_ApplyRoomEdit :  AdminBasePage
    {
        public int ApplyID
        {
            get
            {
                return Utility.Common.GetIntOfUrl("id");
            }
        }
        protected void Page_Load(object sender, EventArgs e)
        {
            AdminPopedom.IsHoldModel("06");
            if (!IsPostBack)
            {
                if (ApplyID <= 0)
                {
                    Response.Write("请勿非法操作！");
                    Response.End();
                }
                BindData();
            }
        }
        //绑定申请的房间信息
        protected void BindData()
        {
            DataTable dt = DbSession.Default.FromSql("select * from Web_VApplyVipRoom where id=" + ApplyID).ToDataTable();
            if (dt.Rows.Count > 0)
            {
                ltlApplyDays.Text = dt.Rows[0]["AppleyDays"].ToString();
                ltlBasePoint.Text = dt.Rows[0]["BasePoint"].ToString();
                ltlComName.Text = dt.Rows[0]["ComName"].ToString();
                ltlDeskCount.Text = dt.Rows[0]["DeskCount"].ToString();
                ltlEmail.Text = dt.Rows[0]["Email"].ToString();
                ltlGameMsg.Text = dt.Rows[0]["RallWelcome"].ToString();
                ltlLessPoint.Text = dt.Rows[0]["LessPoint"].ToString();
                ltlMaxPeople.Text = dt.Rows[0]["MaxPeople"].ToString();
                ltlMaxPoint.Text = dt.Rows[0]["MaxPoint"].ToString();
                ltlMobile.Text = dt.Rows[0]["Mobile"].ToString();

                txtOpenRoomDate.Text = dt.Rows[0]["OpenRoomDate"].ToString();
                ltlPayMoney.Text = (Convert.ToInt32(dt.Rows[0]["EveryDayRent"].ToString()) * Convert.ToInt64(dt.Rows[0]["AppleyDays"].ToString())).ToString();
                ltlQQ.Text = dt.Rows[0]["QQ"].ToString();
                ltlRemark.Text = dt.Rows[0]["Remark"].ToString();
                ltlRoomMsg.Text = dt.Rows[0]["RoomMsg"].ToString();
                ltlRoomName.Text = dt.Rows[0]["RoomName"].ToString();
                ltlRoomPwd.Text = dt.Rows[0]["RoomPwd"].ToString();
                ltlTax.Text = (dt.Rows[0]["TaxType"].ToString() == "0" ? "税率：" + dt.Rows[0]["Tax"].ToString() + "%" : "服务费：" + dt.Rows[0]["Tax"].ToString()+UiCommon.StringConfig.MoneyName);
                ltlUserName.Text = dt.Rows[0]["UserName"].ToString();
                ViewState["status"] = dt.Rows[0]["AuditStatus"].ToString();

            }
        }

        protected void Button1_Click(object sender, EventArgs e)
        {
            if (!CommonManager.Web.CheckPostSource())
                return;
            string status = Utility.Common.GetStringOfForm("status");
            //订单状态变化时
            if (status != ViewState["status"].ToString() && status!="0")
            {
               
                if (ViewState["status"].ToString() == "1")
                {
                    CommonManager.Web.RegJs(this, "alert('已审核通过，不能修改！');", false);
                    return;
                }
                if (ViewState["status"].ToString() == "2")
                {
                    CommonManager.Web.RegJs(this, "alert('已审核不通过，不能修改！');", false);
                    return;
                }
              
               //处理信息
                  Dictionary<string, object> dic = new Dictionary<string, object>();
                  DbSession.Default.FromProc("Web_PApplyVipRoomUpdate").AddInputParameter("@NewStatus", DbType.Int32, status)
                                                                       .AddInputParameter("@ID", DbType.Int32, ApplyID)
                                                                       .AddInputParameter("@OpenRoomDate",DbType.DateTime, txtOpenRoomDate.Text)
                                                                        .AddReturnValueParameter("@ReturnValue", DbType.Int32)
                                                                       .Execute(out dic);
                  if (dic.Count > 0)
                  { 
                     string result = dic["ReturnValue"].ToString();
                     //Response.Write(result);
                     //Response.End();
                     if (result == "-1")
                     {
                         CommonManager.Web.RegJs(this, "alert('已审核通过，不能修改！');", false);
                         return;
                     }
                     else if (result == "-2")
                     {
                         CommonManager.Web.RegJs(this, "alert('玩家游戏中，不能进行金币处理！');", false);
                         return;
                     }
                     else if (result == "0")
                     {
                         CommonManager.Web.RegJs(this, "alert('未知服务器错误！');", false);
                         return;
                     }
                     else {
                         if (Utility.Common.IsIntegrity(result))//返回房间ID
                         {
                             if (status == "1")
                             {
                                 Alert("审核通过！", "GameRoomsEdit.aspx?sid=" + result);
                             }
                             else
                             {
                                 CommonManager.Web.RegJs(this, "alert('操作成功！');",  true );
                                 
                             }
                         }
                     }
                  }
            }
        }
    }
 
