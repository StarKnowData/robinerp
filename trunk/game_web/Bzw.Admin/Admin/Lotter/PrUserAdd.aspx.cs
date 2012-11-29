using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using BCST.Common;
using Bzw.Data;
using System.Data;

 
    public partial class Admin_Lotter_PrUserAdd : AdminBasePage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
              AdminPopedom.IsHoldModel("18");
            if (!IsPostBack)
            {
                DataTable dt = DbSession.Default.FromSql("select ID,LotteryAwardName from Web_LotterAward").ToDataTable();
                CommonManager.Web.BindListControl(dt, ddlAward, "LotteryAwardName", "ID");
                dt.Clear();
            }
        }

        protected void Edit(object sender, EventArgs e)
        {
            string userid = txtUserID.Text.Trim();
            string awardid = ddlAward.SelectedValue;
            if (DbSession.Default.FromSql("select count(1) from Tusers where userid=" + userid).ToScalar().ToString() == "0")
            {
                CommonManager.Web.RegJs(this, "alert('此用户id不存在！');", false);
                return;
            }
            DbSession.Default.FromSql("insert into Web_LotterSpecial(UserID,AwardID,Status,Adddate) values (" + userid + "," + awardid + ",0,getdate())").Execute();
            CommonManager.Web.RegJs(this, "alert('添加成功！');", false);
        }
    }
 
