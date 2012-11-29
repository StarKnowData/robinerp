using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using BCST.Common;
using System.Data;
using Bzw.Data;
using BLL;

 
    public partial class Admin_SConfig_SendMsg : AdminBasePage
    {
        protected int MsgID
        {
            get
            {
                string tmp = CommonManager.Web.Request("mid", "");
                if (!CommonManager.String.IsInteger(tmp))
                    return 0;
                return int.Parse(tmp);
            }
        }
        protected void Page_Load(object sender, EventArgs e)
        {
            AdminPopedom.IsHoldModel("18");
            if (!IsPostBack)
            {
                if (MsgID > 0)
                {
                    DataTable dt = DbSession.Default.FromSql("select * from Web_AdminEmail where MsgID=@MsgID ").AddInputParameter("@MsgID", DbType.Int32, MsgID).ToDataTable();
                    if (dt.Rows.Count > 0)
                    {
                        txtContent.Value = dt.Rows[0]["MsgContent"].ToString();
                        txtSendTime.Value = dt.Rows[0]["SendTime"].ToString();
                        txtUserID.Value = dt.Rows[0]["UserID"].ToString();
                        hida.Value = dt.Rows[0]["IsToAll"].ToString();
                        rdoIsMarquee.SelectedValue = dt.Rows[0]["IsMarquee"].ToString();
                        rdoIsHallMarquee.SelectedValue = dt.Rows[0]["IsHallMarquee"].ToString();
                        if (dt.Rows[0]["IsToAll"].ToString() == "1")
                        {
                            rdoIsToAll.SelectedValue = "1";
                            txtUserID.Disabled = true;
                        }
                        else
                        {
                            rdoIsToAll.Enabled = false;
                        }
                    }
                    dt.Clear();
                    Button1.Text = "修改";
                }
            }
        }

        protected void SendMessage(object sender, EventArgs e)
        {
            string content = txtContent.Value;
            string sendtime = txtSendTime.Value;
            string userids = txtUserID.Value;
             
            if (content.Trim() == ""  || sendtime.Trim() == "")
            {
                Alert("信息内容、发送时间均不能为空！", Request.Url.ToString());

            }
            if (content.Length > 500)
            {
                Alert("信息内容不能超过200字！", Request.Url.ToString());
            }
            if (!CommonManager.String.IsDateTime(sendtime))
            {
                Alert("时间格式不正确！", Request.Url.ToString());
            }
            if (rdoIsToAll.SelectedValue == "0")
            {
                string[] strids = userids.Split(',');
                Member mem = new Member();
                for (int i = 0; i < strids.Length; i++)
                {
                    if (strids[i] != "")
                    {
                         
                    }
                }
            }
            if (MsgID > 0)
            {
                //修改

                DbSession.Default.FromSql("update web_adminEmail set MsgContent=@MsgContent,SendTime=@SendTime,AdminName=@AdminName,IsHallMarquee=@IsHallMarquee where MsgID=@MsgID").AddInputParameter("@MsgContent", DbType.String, content)
                    .AddInputParameter("@SendTime",DbType.DateTime,sendtime) 
                    .AddInputParameter("@MsgID",DbType.Int32,MsgID)
                    .AddInputParameter("@AdminName",DbType.String,AdminUserName)
                    .AddInputParameter("@IsHallMarquee",DbType.Int32,rdoIsHallMarquee.SelectedValue)
                    .Execute();
            }
            else
            {

               //添加
                //添加跑马灯
                if (rdoIsMarquee.SelectedValue == "1" || rdoIsHallMarquee.SelectedValue=="1") {
                    DbSession.Default.FromSql("insert into web_adminEmail(MsgContent,SendTime,AdminName,UserID,IsSend,IsToAll,IsMarQuee,[Type],IsHallMarquee) values(@MsgContent,@SendTime,@AdminName,@UserID,@IsSend,@IsToAll,@IsMarQuee,@Type,@IsHallMarquee)").AddInputParameter("@MsgContent", DbType.String, content)
                           .AddInputParameter("@SendTime", DbType.DateTime, sendtime)
                           .AddInputParameter("@UserID", DbType.String, 0)
                           .AddInputParameter("@AdminName", DbType.String, AdminUserName)
                           .AddInputParameter("@IsSend", DbType.Boolean, false)
                           .AddInputParameter("@IsToAll", DbType.Int32, 0)
                           .AddInputParameter("@IsMarQuee",DbType.Int32,rdoIsMarquee.SelectedValue)
                           .AddInputParameter("@Type",DbType.Int32,1)
                           .AddInputParameter("@IsHallMarquee",DbType.Int32,rdoIsHallMarquee.SelectedValue)
                           .Execute();
                } 
                else
                {
                    //群发
                    if (rdoIsToAll.SelectedValue == "1")
                    {
                        DbSession.Default.FromSql("insert into web_adminEmail(MsgContent,SendTime,AdminName,UserID,IsSend,IsToAll,IsMarQuee,IsHallMarquee) values(@MsgContent,@SendTime,@AdminName,@UserID,@IsSend,@IsToAll,@IsMarQuee,0)").AddInputParameter("@MsgContent", DbType.String, content)
                           .AddInputParameter("@SendTime", DbType.DateTime, sendtime)
                           .AddInputParameter("@UserID", DbType.String, 0)
                           .AddInputParameter("@AdminName", DbType.String, AdminUserName)
                           .AddInputParameter("@IsSend", DbType.Boolean, false)
                           .AddInputParameter("@IsToAll", DbType.Int32, 1)
                            .AddInputParameter("@IsMarQuee", DbType.Int32, 0)
                           .Execute();
                    }
                    else
                    {
                        string[] strids = userids.Split(',');
                        for (int i = 0; i < strids.Length; i++)
                        {
                            if (strids[i] != "")
                            {
                                DbSession.Default.FromSql("insert into web_adminEmail(MsgContent,SendTime,AdminName,UserID,IsSend,IsToAll,IsMarQuee) values(@MsgContent,@SendTime,@AdminName,@UserID,@IsSend,@IsToAll,@IsMarQuee)").AddInputParameter("@MsgContent", DbType.String, content)
                           .AddInputParameter("@SendTime", DbType.DateTime, sendtime)
                           .AddInputParameter("@UserID", DbType.Int32, strids[i])
                           .AddInputParameter("@AdminName", DbType.String, AdminUserName)
                           .AddInputParameter("@IsSend", DbType.Int32, 0)
                           .AddInputParameter("@IsToAll", DbType.Int32, 0)
                            .AddInputParameter("@IsMarQuee", DbType.Int32, 1)
                           .Execute();
                            }
                        }
                    }
                }
            }
            CommonManager.Web.RegJs(this, "alert('操作成功！');location.href='AdminMsgList.aspx';", false);
        }
    }
 
