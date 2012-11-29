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
using BCST.Common;
using Bzw.Data;

public partial class Admin_Agency_LinkCurrentDownAgency :AdminBasePage
{
	private int _totalNum;
	public int TotalNum
	{
		get
		{
			return _totalNum;
		}
		set
		{
			_totalNum = value;
		}
	}

	private long _totalMoney;
    public long TotalMoney
	{
		get
		{
			return _totalMoney;
		}
		set
		{
			_totalMoney = value;
		}
	}

	public string AgencyName
	{
		get
		{
			return ViewState["AgencyName"].ToString();
		}
		set
		{
			ViewState["AgencyName"] = value;
		}
	}

	IAgency agency = new Agency();

    //protected int PageIndex
    //{
    //    get
    //    {
    //        string tmp = CommonManager.Web.Request( "page", "" );
    //        if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
    //            return 1;
    //        return int.Parse( tmp );
    //    }
    //}

	protected void Page_Load( object sender, EventArgs e )
	{
		 

        this.AgencyName = CommonManager.Web.Request("AgencyName", "");
		if( string.IsNullOrEmpty( AgencyName ) )
		{
			CommonManager.Web.RegJs( this, "alert('参数错误！');history.back();", false );
			return;
		}

		if( this.IsPostBack )
			return;
		InitdataBind();
	}
	/// <summary>
	/// 初始绑定.由左边的树目录为传过来。如果没有传入。则取整个系统登入用户。Session[]
	/// </summary>
	public void InitdataBind()
	{
        /*
		IAgency agency = new Agency();
		SqlDataReader dr = null;
		int ParentAgencyID = 0;

		dr = agency.GetSingleAgency( AgencyName ); 
		try
		{
			if( dr.Read() )
			{
				ParentAgencyID = Convert.ToInt32( dr["AgencyID"] );
			}
		}
		catch( Exception ex )
		{
			throw ex;
		}
		finally
		{
			dr.Close();
		}
        */

        string ParentAgencyID = new BLL.Agency().GetAgencyIdByName(AgencyName);
        
		string sqlCondition = " And ParentAgencyID = " + ParentAgencyID;

		string searchkey = CommonManager.Web.RequestUrlDecode( "key", "" );
		if( !string.IsNullOrEmpty( searchkey ) )
		{
			sqlCondition += " and (AgencyName='" + searchkey + "' or TrueName='" + searchkey + "') ";
		}

		int counts;
		DataTable dt = Agency.Default.AgencyList( "*", "AgencyID", 1, anpPageIndex.PageSize, PageIndex, out counts, sqlCondition );
		anpPageIndex.RecordCount = counts;
		anpPageIndex.CurrentPageIndex = PageIndex;

		rptDownAgencyList.DataSource = dt;
		rptDownAgencyList.DataBind();

        TotalMoney = DbSession.Default.FromSql("select ISNULL(Sum(convert(bigint,Account)),0) from web_agency where ParentAgencyID=" + ParentAgencyID).ToScalar<long>();
	}
}
