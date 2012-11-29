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
using System.Data.SqlClient;
using System.IO;

public partial class Admin_Agency_AgencyDetailInfo : AdminBasePage
{
	BLL.Agency agency = new BLL.Agency();

	protected void Page_Load( object sender, EventArgs e )
	{
        AdminPopedom.IsHoldModel("17");

        GetParentChildSV();

		if( !IsPostBack )
		{
			BindData();
		}
	}

	public void BindData()
	{
        DataRow dr = agency.GetInfo(AgencyID);
		if( dr != null )
		{
			tbxUser.Text = dr["AgencyName"].ToString();
			tbxDomain.Text = dr["DomainUrl"].ToString();
			tbxName.Text = dr["TrueName"].ToString();
			tbxBankName.Text = dr["BankName"].ToString();
			tbxAccountNo.Text = dr["AccountNO"].ToString();
			tbxAccountName.Text = dr["AccountName"].ToString();
			tbxBankAddress.Text = dr["BankAddress"].ToString();
			tbxPayorNo.Text = dr["PayorNo"].ToString();
			tbxPhone.Text = dr["Phone"].ToString();
			tbxAddress.Text = dr["Address"].ToString();
			tbxEmail.Text = dr["Email"].ToString();
			tbxPostalCode.Text = Convert.ToInt32( dr["PostalCode"] ) == 0 ? "" : dr["PostalCode"].ToString();
			tbxMobile.Text = dr["MobilPhone"].ToString();
			tbxQQ.Text = dr["QQNum"].ToString();
			txtRemark.Text = dr["Remark"].ToString();
			txtTenpayNo.Text = dr["TenpayNo"].ToString();

		//	txtQQGroup.Text=dr["QQGroupNum"].ToString();

            string spareValue = dr["SpareValue"].ToString();
            tbxSpareValue.Text = spareValue;
            //if (spareValue.Trim() == "100")
            //{
            //    tbxSpareValue.ReadOnly = true;
            //    tbxSpareValue.BackColor = System.Drawing.Color.Gainsboro;
            //}

            try
            {
                int parentId = Convert.ToInt32(dr["ParentAgencyID"]);
                if (parentId == 0)
                {
                    tbxSpareValue.ReadOnly = true;
                    tbxSpareValue.BackColor = System.Drawing.Color.Gainsboro;
                }
            }
            catch //(InvalidCastException ex)
            {

            }
		}
	}

    public void GetParentChildSV()
    {
        string[] temp = agency.GetParentChildSV(AgencyID);
        this.ParentSV = temp[0];
        this.ChildSV = temp[1];
    }

	protected void btnSave_Click( object sender, EventArgs e )
	{
        if(!BCST.Common.CommonManager.Web.CheckPostSource())
        {
            return;
        }

        //---
        if (tbxPassword.Text.Trim().Length > 0)
        {
            if (tbxPassword.Text.Trim().ToLower() != tbxPassword2.Text.Trim())
            {
                lblMsg.Text = "两次输入的帐号密码不一致，请重新输入！";
                return;
            }
        }

		//----
		if( tbxDomain.Text.Trim().Length == 0 )
		{
			tbxDomain.Text = tbxUser.Text.Trim();
		}

        //---
        string spareValue = tbxSpareValue.Text.Trim();
        if (!BCST.Common.CommonManager.String.IsInteger(spareValue))
        {
            lblMsg.Text = "门票比例请输入整数！";
            return;
        }
        else if (agency.ExistDomain(AgencyID, tbxDomain.Text.Trim()))
        {
            lblMsg.Text = "代理商二级域名已存在，请重新输入！";
            return;
        }

		//----
		if( tbxPostalCode.Text.Trim().Length == 0 )
		{
			tbxPostalCode.Text = "0";
		}

		int iRows = 0;
        iRows = new BLL.Agency().Update(AgencyID, tbxPassword.Text.Trim(), tbxName.Text.Trim(), tbxPhone.Text.Trim(), tbxAddress.Text.Trim(), tbxPostalCode.Text.Trim(), 
                        tbxQQ.Text.Trim(), tbxEmail.Text.Trim(), tbxMobile.Text.Trim(), tbxAccountNo.Text.Trim(),tbxAccountName.Text.Trim(), tbxBankName.Text.Trim(),
                        tbxBankAddress.Text.Trim(), tbxPayorNo.Text.Trim(), tbxDomain.Text.Trim(), txtRemark.Text.Trim(), txtTenpayNo.Text.Trim(),
                        tbxSpareValue.Text.Trim(), AdminInfo["ID"].ToString());

      
        if (iRows == 0)
        {
        
            lblMsg.Text = "代理商资料修改成功！" + DateTime.Now;
            //Response.Redirect("AgencyView.aspx");
        }
        else if (iRows == -2)
        {
            lblMsg.Text = "二级域名已存在，请重新输入！";
            return;
        }
        else if (iRows == -3 || iRows == -4)
        {
            lblMsg.Text = "门票比例不能超出允许的变动范围！";
            return;
        }
        else
        {
            
            lblMsg.Text = "代理商资料修改失败！";
        }

        /*
 
        string agencyID = Utility.Common.GetStringOfUrl( "agencyid" );

		//----
		if( tbxDomain.Text.Trim().Length == 0 )
		{
			tbxDomain.Text = tbxUser.Text.Trim();
		}

		if( agency.ExistDomain( agencyID, tbxDomain.Text.Trim() ) )
		{
			lblMsg.Text = "二级域名已存在，请重新输入！";
			return;
		}

		//----
		if( tbxPostalCode.Text.Trim().Length == 0 )
		{
			tbxPostalCode.Text = "0";
		}
         
        
        int iRows = 0;
		if( tbxPassword.Text.Trim().Length > 0 )
		{
			iRows = new BLL.Agency().Update( agencyID, tbxPassword.Text.Trim(), tbxName.Text.Trim(), tbxPhone.Text.Trim(),
				tbxAddress.Text.Trim(), tbxPostalCode.Text.Trim(), tbxQQ.Text.Trim(), tbxEmail.Text.Trim(), tbxMobile.Text.Trim(), tbxAccountNo.Text.Trim(),
				tbxAccountName.Text.Trim(), tbxBankName.Text.Trim(), tbxBankAddress.Text.Trim(), tbxPayorNo.Text.Trim(), tbxDomain.Text.Trim(), txtRemark.Text.Trim(), txtTenpayNo.Text.Trim() );
		}
		else
		{
			iRows = new BLL.Agency().UpdateNotPwd( agencyID, tbxName.Text.Trim(), tbxPhone.Text.Trim(),
				tbxAddress.Text.Trim(), tbxPostalCode.Text.Trim(), tbxQQ.Text.Trim(), tbxEmail.Text.Trim(), tbxMobile.Text.Trim(), tbxAccountNo.Text.Trim(),
				tbxAccountName.Text.Trim(), tbxBankName.Text.Trim(), tbxBankAddress.Text.Trim(), tbxPayorNo.Text.Trim(), tbxDomain.Text.Trim(), txtRemark.Text.Trim(), txtTenpayNo.Text.Trim() );
		}

        BLL.AdminLog alog = new BLL.AdminLog();
		if( iRows > 0 )
		{
            alog.Add(UiCommon.AdminLoginInfo.UserName, "修改代理商[" + tbxUser.Text.Trim() + "]的资料");
			Response.Redirect( "AgencyView.aspx" );

		}
		else
		{
			alog.Add( UiCommon.AdminLoginInfo.UserName, "修改代理商资料失败" );
			lblMsg.Text = "修改失败！";
		}*/
  
    }

    public string AgencyID
    {
        get { return Utility.Common.GetIntOfUrl("agencyid").ToString(); }
    }

    public string ParentSV
    {
        get
        {
            if (ViewState["psv"] != null)
            {
                return ViewState["psv"].ToString();
            }

            return "0";
        }

        set { ViewState["psv"] = value; }
    }

    public string ChildSV
    {
        get
        {
            if (ViewState["csv"] != null)
            {
                return ViewState["csv"].ToString();
            }

            return "0";
        }

        set { ViewState["csv"] = value; }
    }
}
