using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using BCST.Common;
using System.Text;


public partial class Admin_SConfig_ClearList : AdminBasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("03");
        //清除记录
        if (!IsPostBack)
        {
            Clear();

            ltMsg.Text = Utility.Common.GetStringOfUrl("msg");
            BindList();
        }

    }
    private void BindList()
    {
        //获取数据
        DataTable dt = Utility.SqlHelper.ExecuteDataset(CommandType.Text, "select * from dbo.Web_VDataList order by TypeID", null).Tables[0];
        rpList.DataSource = dt.DefaultView;
        rpList.DataBind();
    }
    public void Clear()
    {
        string act = Utility.Common.GetStringOfUrl("action");
        string id = Utility.Common.GetStringOfUrl("typeid");
        string typeName = Utility.Common.GetStringOfUrl("typename");
        string clearTM = Utility.Common.GetStringOfUrl("tm");
        string tableName = Utility.Common.GetStringOfUrl("tabname");
        if (act.ToLower() == "clear" && CommonManager.String.IsInteger(id) && CommonManager.String.IsDateTime(clearTM))
        {
            StringBuilder cmdText = new StringBuilder("");
            string clearEndTM = " DATEADD(dd,1,'" + clearTM + " 00:00:00') ";
            switch (Convert.ToInt32(id))
            {
                case 1: //游戏记录
                    cmdText.AppendFormat(" DELETE TChangeRecordUser where RecordIndex in (select ID from TChangeRecord where EndTime < {0}) ; ", clearEndTM);
                    cmdText.AppendFormat(" DELETE TChangeRecord where EndTime < {0} ; ", clearEndTM);
                    break;
                case 2: //玩家充值记录
                    cmdText.AppendFormat(" DELETE Web_RMBCost where AddTime < {0} ; ", clearEndTM);
                   
                    break;
                case 3: //玩家兑换记录
                    cmdText.AppendFormat(" DELETE Web_Exchange  where UserType=2 and (ApplyState=2 or ApplyState=3) and AddTime < {0} ; ", clearEndTM);
                    break;
                case 4: //玩家金币变化日志
                    cmdText.AppendFormat(" DELETE Web_MoneyChangeLog where [datetime] < {0} ; ", clearEndTM);
                    break;
                case 5: //玩家抽奖记录
                    cmdText.AppendFormat(" DELETE Web_LotterLog where AddDate < {0} ; ", clearEndTM);
                    break;
                case 6: //转账记录
                    cmdText.AppendFormat(" DELETE Web_TransLog where TransTime < {0} ; ", clearEndTM);
                    break;
                case 7: //时局赠送金币日志
                    cmdText.AppendFormat(" DELETE TSendMoneyRecord_New where SendDate < {0} ; ", clearEndTM);
                    break;
                case 8: //玩家反馈记录
                    cmdText.AppendFormat(" DELETE Web_msg where msgtime < {0} ; ", clearEndTM);
                    break;
                case 9: //领取金币日志
                    cmdText.AppendFormat(" DELETE TReceiveMoneyRecord where LastReceiveTime < {0} ; ", clearEndTM); break;
                case 10://玩家登录记录日志
                    cmdText.AppendFormat("Delete TLoginRecord where LastLoginTM < {0};", clearEndTM);
                    break;

            }

            if (cmdText.ToString().Trim().Length == 0)
                Response.Redirect("ClearList.aspx");
 
            int cnt = Utility.SqlHelper.ExecuteNonQuery(CommandType.Text, cmdText.ToString(), null);

            Utility.SqlHelper.ExecuteNonQuery(CommandType.Text, " insert into Web_DataClearLog values(" +AdminUserID + ",'" + AdminUserName + "'," + id + ",'" + typeName + "','" + clearTM + "'," + cnt + ",getdate()) ", null);

            string msg = "清理了[" + typeName + "]，截止时间为" + clearTM + "(含" + clearTM + ")日以前的数据，共" + cnt + "笔记录";

            Response.Redirect("ClearList.aspx?msg=" + Server.UrlEncode("<span style='color:red;'>信息：</span>" + msg + "，操作时间为：" + DateTime.Now));
        }
    }

}