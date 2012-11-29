using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using BCST.Common;
using System.Data;
using Bzw.Data;

 
    public partial class Admin_Games_GameContestRoomsWrite : AdminBasePage
    {
        protected int RoomID
        {
            get
            {
                string tmp = Utility.Common.GetStringOfUrl("id");
                if (string.IsNullOrEmpty(tmp) || !CommonManager.String.IsInteger(tmp))
                    return 0;
                return int.Parse(tmp);
            }
        }
        protected void Page_Load(object sender, EventArgs e)
        {
            AdminPopedom.IsHoldModel("06");
            if (!IsPostBack)
            {
                   DataTable dt1 = DbSession.Default.FromSql("select * from Web_MatchSendType").ToDataTable();
            ddlSendType.DataSource = dt1;
            ddlSendType.DataTextField = "Name";
            ddlSendType.DataValueField = "ID";
            ddlSendType.DataBind();
                if (RoomID != 0)
                {
                    DataTable dt = DbSession.Default.FromSql("select * from TContestInfo where ContestID=" + RoomID).ToDataTable();
                    if (dt.Rows.Count > 0)
                    {
                        txtBeginTime.Text = dt.Rows[0]["StartTime"].ToString();
                        txtChip.Text = dt.Rows[0]["Chip"].ToString();
                        txtEndTime.Text = dt.Rows[0]["EndTime"].ToString();
                        txtEntryFee.Text = dt.Rows[0]["EntryFee"].ToString();
                        txtLowCount.Text = dt.Rows[0]["LowCount"].ToString();
                        txtMessage.Text = dt.Rows[0]["Message"].ToString();
                        txtUpPeople.Text = dt.Rows[0]["UpPeople"].ToString();
                        txtSendTime.Text = dt.Rows[0]["SendTime"].ToString();
                        txtAwardContent.Value = dt.Rows[0]["AwardContent"].ToString();
                        txtTimeLimit.Text = dt.Rows[0]["TimeOut"].ToString();
                        txtLowChip.Text = dt.Rows[0]["LowChip"].ToString();
                        ddlSendType.SelectedValue = dt.Rows[0]["SendTypeID"].ToString();
                        txtMatchContent.Value = dt.Rows[0]["MatchContent"].ToString();
                    }
                }
            }
         
        }

        protected void btnSubmit_Click(object sender, EventArgs e)
        {
            
            if (!CommonManager.Web.CheckPostSource())
                return;
            if (!IsValid)
                return;

            if (!CommonManager.String.IsInteger(txtChip.Text.Trim()) || !CommonManager.String.IsInteger(txtLowCount.Text.Trim()) || !CommonManager.String.IsInteger(txtUpPeople.Text.Trim()) || !CommonManager.String.IsInteger(txtUpPeople.Text.Trim()))
            {
                CommonManager.Web.RegJs(this, "alert('比赛积分、最少局数、报名费用、比赛人数上限必须为整数！');", false);
                return;
            }
            if (RoomID != 0)
            {
                //修改
            
                string sql = @"update TContestInfo set StartTime=@StartTime,EndTime=@EndTime,Chip=@Chip,LowCount=@LowCount,EntryFee=@EntryFee,UpPeople=@UpPeople,Message=@Message,SendTime=@SendTime,AwardContent=@AwardContent,LowChip=@LowChip,[TimeOut]=@TimeOut,[SendTypeID]=@SendTypeID,MatchContent=@MatchContent where ContestID=@ContestID";
                DbSession.Default.FromSql(sql)
                    .AddInputParameter("@StartTime", DbType.DateTime, txtBeginTime.Text.Trim())
                    .AddInputParameter("@EndTime",DbType.DateTime,txtEndTime.Text.Trim())
                    .AddInputParameter("@Chip",DbType.Int64,txtChip.Text.Trim())
                    .AddInputParameter("@ContestID", DbType.Int32, RoomID)
                    .AddInputParameter("@LowCount",DbType.Int32,txtLowCount.Text.Trim())
                    .AddInputParameter("@EntryFee",DbType.Int64,txtEntryFee.Text.Trim())
                    .AddInputParameter("@UpPeople",DbType.Int32,txtUpPeople.Text.Trim())
                    .AddInputParameter("@Message",DbType.String,txtMessage.Text)
                    .AddInputParameter("@SendTime",DbType.DateTime,txtSendTime.Text.Trim())
                    .AddInputParameter("@AwardContent", DbType.String, txtAwardContent.Value)
                    .AddInputParameter("@LowChip",DbType.Int64,txtLowChip.Text.Trim())
                    .AddInputParameter("@TimeOut",DbType.Int32,txtTimeLimit.Text.Trim())
                    .AddInputParameter("@SendTypeID",DbType.Int32,ddlSendType.SelectedValue)
                    .AddInputParameter("@MatchContent",DbType.String,txtMatchContent.Value)
                    .Execute();
                Alert("操作成功！", "GameContestRooms.aspx");
            }
            else
            { 
            //添加
                string sql = @"INSERT  INTO dbo.TContestInfo
                            (
                              
                              StartTime ,
                              EndTime ,
                              Chip ,
                              LowCount ,
                              EntryFee ,
                              UpPeople ,
                              Message ,
                              SendTime,
                              AwardContent,
                              LowChip,
                              [TimeOut],
                              [SendTypeID],
                                [MatchContent]
                            )
                    VALUES  ( 
                              
                            @StartTime , -- StartTime - datetime
                             @EndTime, -- EndTime - datetime
                              @Chip , -- Chip - bigint
                              @LowCount , -- LowCount - int
                              @EntryFee , -- EntryFee - bigint
                              @UpPeople, -- UpPeople - int
                              @Message , -- Message - nvarchar(50)
                              @SendTime , -- SendTime - datetime
                              @AwardContent,
                              @LowChip,
                              @TimeOut,
                              @SendTypeID,
                              @MatchContent
                            )";
                DbSession.Default.FromSql(sql)
                      .AddInputParameter("@StartTime", DbType.DateTime, txtBeginTime.Text.Trim())
                    .AddInputParameter("@EndTime", DbType.DateTime, txtEndTime.Text.Trim())
                    .AddInputParameter("@Chip", DbType.Int64, txtChip.Text.Trim()) 
                    .AddInputParameter("@LowCount", DbType.Int32, txtLowCount.Text.Trim())
                    .AddInputParameter("@EntryFee", DbType.Int64, txtEntryFee.Text.Trim())
                    .AddInputParameter("@UpPeople", DbType.Int32, txtUpPeople.Text.Trim())
                    .AddInputParameter("@Message", DbType.String, txtMessage.Text)
                    .AddInputParameter("@SendTime", DbType.DateTime, txtSendTime.Text.Trim())
                     .AddInputParameter("@AwardContent", DbType.String, txtAwardContent.Value)
                     .AddInputParameter("@LowChip",DbType.Int64,txtLowChip.Text.Trim())
                      .AddInputParameter("@TimeOut", DbType.Int32, txtTimeLimit.Text.Trim())
                     .AddInputParameter("@SendTypeID", DbType.Int32, ddlSendType.SelectedValue)
                     .AddInputParameter("@MatchContent",DbType.String,txtMatchContent.Value)
                    .Execute();
                Alert("操作成功！", "GameContestRooms.aspx");
            }
        }
    }
 
