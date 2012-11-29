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
using BCST.Common;

public partial class Admin_Users_CreateUser :AdminBasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("04");
    }

    protected void CreateUserClick(object sender, EventArgs e)
    {
        string username = string.Empty, nickname = string.Empty, pwd = string.Empty,idcard=string.Empty,realname=string.Empty;
        username = CommonManager.Web.RequestForm("u", "");

        BLL.Member member = new BLL.Member();
        if (member.ExistName(username))
        {
            this.ErrorLabel.Text = "该用户名已经存在！";
            return;
        }

        nickname =Server.HtmlDecode(CommonManager.Web.RequestForm("n", "").Replace(",","''"));
        if (member.ExistNick(nickname))
        {
            this.ErrorLabel.Text = "该昵称已经存在！";
            return;
        }
        pwd = CommonManager.Web.RequestForm("pwd", "");

		idcard = CommonManager.Web.RequestForm("idcard", "");
		realname = CommonManager.Web.RequestForm("realname", "");

        int dbLogoId = member.SetLogoID(1, 1);

		int userId = member.Add_UserInfo(username, nickname, string.Empty, 1, dbLogoId, pwd, pwd, idcard, string.Empty, string.Empty, Utility.Common.RequestIP, string.Empty, realname);
        if( userId > 0 )
		{
            this.ErrorLabel.ForeColor=System.Drawing.Color.Green;
            this.ErrorLabel.Text = "用户创建成功！";
		}
		else
		{
            this.ErrorLabel.Text = "抱歉，创建失败，可能是服务器繁忙，请稍后再试！！";
	
		}

    
    }


}
