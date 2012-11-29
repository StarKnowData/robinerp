using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using BCST.Common;
using System.Data;
using Bzw.Data;

 
    public partial class Admin_SConfig_SendMsg2 : AdminBasePage
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
                        content.Value = dt.Rows[0]["MsgWebContent"].ToString();
                        txtSendTime.Value = dt.Rows[0]["SendTime"].ToString(); 
                    }
                    dt.Clear();
                    Button1.Text = "修改";
                }
            }
        }

        protected void SendMessage(object sender, EventArgs e)
        {
            
            string con = content.Value;
            string sendtime = txtSendTime.Value;
            if (!CommonManager.String.IsDateTime(sendtime))
            {
                Alert("时间格式不正确！", Request.Url.ToString());
            }
            if (MsgID ==0)
            {
                int maxID = (int)DbSession.Default.FromSql("select isnull(max(MsgID),0) from Web_AdminEmail").ToScalar();
                DbSession.Default.FromSql("insert into web_adminEmail(MsgContent,SendTime,AdminName,UserID,IsSend,IsToAll,IsMarQuee,[Type],MsgWebContent) values(@MsgContent,@SendTime,@AdminName,@UserID,@IsSend,@IsToAll,@IsMarQuee,@Type,@MsgWebContent)").AddInputParameter("@MsgContent", DbType.String, "/Html/Msg/MsgHtml"+(maxID+1)+".html")
                         .AddInputParameter("@SendTime", DbType.DateTime, sendtime)
                         .AddInputParameter("@UserID", DbType.String, 0)
                         .AddInputParameter("@AdminName", DbType.String, AdminUserName)
                         .AddInputParameter("@IsSend", DbType.Boolean, false)
                         .AddInputParameter("@IsToAll", DbType.Int32, 0)
                         .AddInputParameter("@IsMarQuee", DbType.Int32, 0)
                         .AddInputParameter("@Type", DbType.Int32, 2)
                          .AddInputParameter("@MsgWebContent", DbType.Int32, con)
                         .Execute();
                
                string[] param = new string[4];
                param[0] = con;
                CreateHtml ct = new CreateHtml();
                ct.FileName = "MsgHtml" + (maxID+1) + ".html";
             
            ct.MakeHtml("/Html/Msg", "", Server.MapPath("/Html/Msg"),Server.MapPath( "/Html/Msg/Templates.html"), param);
            
                CommonManager.Web.RegJs(this, "alert('操作成功！');location.href='AdminMsgList.aspx';", false);
            }
            else
            {
                DbSession.Default.FromSql("update web_adminEmail set MsgWebContent=@MsgWebContent,SendTime=@SendTime,AdminName=@AdminName where MsgID=@MsgID").AddInputParameter("@MsgWebContent", DbType.String, con)
                       .AddInputParameter("@SendTime", DbType.DateTime, sendtime)
                       .AddInputParameter("@MsgID", DbType.Int32, MsgID)
                       .AddInputParameter("@AdminName", DbType.String, AdminUserName)
                       .Execute();
                CreateHtml ct = new CreateHtml();
                ct.DeleteHtml(Server.MapPath("/Html/Msg/Msg" + MsgID + ".html"));
                string[] param = new string[4];
                param[0] = con;
                ct.FileName = "MsgHtml" + MsgID + ".html";
                ct.MakeHtml("/Html/Msg", "",  Server.MapPath("/Html/Msg"),Server.MapPath("/Html/Msg/Templates.html"), param);
                CommonManager.Web.RegJs(this, "alert('操作成功！');location.href='AdminMsgList.aspx';", false);
            }
            
        }
    }
 
