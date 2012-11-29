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
using System.Text;

using Utility;
using BCST.Common;
using Bzw.Data;

public partial class Admin_Edit_AdminUser : AdminBasePage
{
    public string Admin_Userids; //ID号
    public string List_AdminSupport; //权限列表
    //string MD5AdminPwd;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel(string.Empty);

		string tmp = CommonManager.Web.Request( "id", "" );
		if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
		{
			Alert( "请勿非法操作！", null );
			return;
		}
		else
        {
			Admin_Userids = tmp; //Limit.getFormValue("id");

            if (!Page.IsPostBack)
            {
                BindModelList();
                Edit_AdminUsers();
            }
        }
    }

    //绑定模块列表
    public void BindModelList()
    {
		DataTable dt = DbSession.Default.FromSql( "select ModelNo,ModelName from Web_Manage_Model" ).ToDataTable(); //sqlconn.sqlReader("select ModelNo,ModelName from Web_Manage_Model");
        if (dt.Rows.Count > 0)
        {
            for (int i = 0; i < dt.Rows.Count; i++)
            {
                this.chkListModels.Items.Add(new ListItem(dt.Rows[i]["ModelName"].ToString(), dt.Rows[i]["ModelNo"].ToString()));
            }
        }
    }

    protected void Edit_AdminUsers()
    {
        DataTable sd = new DataTable();
        string sql = "select UserName,PassWord,UserGroup from [web_manage_admin] Where Id ='" + Admin_Userids + "'";
		sd = DbSession.Default.FromSql( sql ).ToDataTable();//sqlconn.sqlReader(sql);
        if (sd.Rows.Count > 0)
        {
            this.AdminName.Text = sd.Rows[0]["Username"].ToString();
            List_AdminSupport = sd.Rows[0]["UserGroup"].ToString();
            if (Convert.ToInt32(List_AdminSupport.Trim()) == 2)
            {
                trPopedom.Attributes.Add("style", "display:none;");
            }
            else
            {
                //read admin popedom info
				DataTable dtPopedom = DbSession.Default.FromSql( "select ModelNo from Web_Manage_Popedom where AdminID=" + Admin_Userids ).ToDataTable(); //sqlconn.sqlReader("select ModelNo from Web_Manage_Popedom where AdminID=" + Admin_Userids);
                if (dtPopedom.Rows.Count > 0)
                {
                    string sModelNo = string.Empty;
                    for (int i = 0; i < dtPopedom.Rows.Count; i++)
                    {
                        sModelNo = dtPopedom.Rows[i]["ModelNo"].ToString().Trim().ToLower();
                        foreach (ListItem li in chkListModels.Items)
                        {
                            if (sModelNo == li.Value.Trim().ToLower())
                            {
                                li.Selected = true;
                                continue;
                            }
                        }
                    }
                }
                dtPopedom.Clear();
            }
        }
        sd.Clear();
    }

    protected void EditAdminUser(object sender, EventArgs e)
    {

        string SqlAdminName, SqlAdminPwd;
        SqlAdminName =Utility.Common.FilterString ( AdminName.Text.Trim());
        SqlAdminPwd = AdminPwd.Text.Trim();

		string sql = "update web_manage_admin set UserName=@UserName";
		if( !string.IsNullOrEmpty( SqlAdminPwd ) )
			sql += ",PassWord=@PassWord";
		sql += " where ID=@ID";

		int SqlState = DbSession.Default.FromSql( sql )
						.AddInputParameter( "@UserName", DbType.String, SqlAdminName )
						.AddInputParameter( "@PassWord", DbType.String, CommonManager.String.EncryptMD5SystemDefaultMethod( SqlAdminPwd, true, true ) )
						.AddInputParameter( "@ID", DbType.String, Admin_Userids )
						.Execute();

        StringBuilder sbPopedom = new StringBuilder(" delete Web_Manage_Popedom where AdminID=" + Admin_Userids + ";");
        foreach (ListItem li in chkListModels.Items)
        {
            if (li.Selected)
            {
                sbPopedom.Append("  insert into Web_Manage_Popedom (AdminID,ModelNo) values (" + Admin_Userids + ",'" + li.Value + "'); ");
            }
        }
        if (sbPopedom.ToString().Trim().Length > 0)
        {
            //sqlconn.sql_Exec(sbPopedom.ToString());
			DbSession.Default.FromSql( sbPopedom.ToString() ).Execute();
        }
        string adminName = AdminInfo["UserName"].ToString();
        string descript = "修改管理员信息！帐号：" + SqlAdminName;
        string system = Common.GetOS;
        if (SqlState >= 0)
        {
            new BLL.Member().InsertAdminModifyLog(adminName, Common.RequestIP, system, descript, 1);
            Alert("温馨提示:\\n\\n操作成功！", "Add_AdminUser.aspx");
        }
        else
        {
            new BLL.Member().InsertAdminModifyLog(adminName, Common.RequestIP, system, descript, 0);
			Alert( "温馨提示:\\n\\n操作失败！", null );
        }

    }

}
