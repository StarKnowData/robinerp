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
using Bzw.Data;
using BCST.Common;

public partial class Admin_Trans_Trans : AdminBasePage
{
	public int tableids;
	public string titlenames;
	string times;
	string para = "";
	string SqlW;
	string action;

	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "08" );

		TransLinfo();
	}

	protected void TransLinfo()
	{
		//action = Limit.getFormValue("act");
		action = Request.QueryString["act"];
		if( action == "post" )
		{
			para += "act=post";
			string rr = "", zz = "", jj = "", ii = "", t1 = "", t2 = "", mr = "", mm = "", sr = "", ss = "",zd="",hd="";

			rr = Request.QueryString["rr"];  //记录数
			zz = Request.QueryString["zz"];  //转账人
			jj = Request.QueryString["jj"];  //收款人
			ii = Request.QueryString["ii"];  //IP地址
			t1 = Request.QueryString["t1"];  //查询开始时间
			t2 = Request.QueryString["t2"];  //查询结束时间
			mr = Request.QueryString["mr"];  //金币判断
			mm = Request.QueryString["mm"];  //金币数
			sr = Request.QueryString["sr"];  //扣手续费判断
			ss = Request.QueryString["ss"];  //扣手续费数
			hd = Request.QueryString["hd"];
			zd = Request.QueryString["zd"];
			/*
			string rr, zz, jj, ii, t1, t2, mr, mm, sr, ss;
			rr = Limit.editCharacter(Limit.getFormValue("rr"));      //记录数
			zz = Limit.editCharacter(Limit.getFormValue("zz"));      //转账人
			jj = Limit.editCharacter(Limit.getFormValue("jj"));      //收款人
			ii = Limit.editCharacter(Limit.getFormValue("ii"));      //IP地址
			t1 = Limit.editCharacter(Limit.getFormValue("t1"));    //查询开始时间
			t2 = Limit.editCharacter(Limit.getFormValue("t2"));    //查询结束时间
			mr = Limit.editCharacter(Limit.getFormValue("mr"));    //金币判断
			mm = Limit.editCharacter(Limit.getFormValue("mm"));      //金币数
			sr = Limit.editCharacter(Limit.getFormValue("sr"));    //扣手续费判断
			ss = Limit.editCharacter(Limit.getFormValue("ss"));      //扣手续费数
            
			//Response.Write(mr);
			//Response.Write(zz);
			//Response.Write(jj);
			if (!CommonManager.String.IsInteger(rr)) rr = "0";
			if (!CommonManager.String.IsInteger(t1)) t1 = "0";
			if (!CommonManager.String.IsInteger(t2)) t2 = "0";
			if (!CommonManager.String.IsInteger(mm)) mm = "0";
			if (!CommonManager.String.IsInteger(ss)) ss = "0"; */
			if( rr == null || !CommonManager.String.IsInteger( rr ) )
				rr = "0";
			if (t1 == null || !CommonManager.String.IsInteger(t1))
			{
				//t1 = "0";
				CommonManager.Web.RegJs(this, "alert('温馨提示：\\n\\n[划账时间]输入值必须为数字！');location.href='TransSeach.aspx';", false);
				return;
			}
			if (t2 == null || !CommonManager.String.IsInteger(t2))
			{
				//t2 = "0";
				CommonManager.Web.RegJs(this, "alert('温馨提示：\\n\\n[划账时间]输入值必须为数字！');location.href='TransSeach.aspx';", false);
				return;
			}
			if( mm == null || !CommonManager.String.IsInteger( mm ) )
			{
				//mm = "0";
				CommonManager.Web.RegJs(this, "alert('温馨提示：\\n\\n[划账金币数]输入值必须为数字！');location.href='TransSeach.aspx';", false);
				return;
			}
			if( ss == null || !CommonManager.String.IsInteger( ss ) )
			{
				//ss = "0";
				CommonManager.Web.RegJs(this, "alert('温馨提示：\\n\\n[扣手续费]输入值必须为数字！');location.href='TransSeach.aspx';", false);
				return;
			}
			if( Convert.ToInt32( t1 ) > Convert.ToInt32( t2 ) )
			{
				//Alert( "温馨提示：\\n\\n划帐时间，前面输入的数必须小于或等于后面输入的数！", null );
				CommonManager.Web.RegJs(this, "alert('温馨提示：\\n\\n[划账时间]前面输入的数必须小于或等于后面输入的数！');location.href='TransSeach.aspx';", false);
				return;
				
			}
			if( hd != "" && !CommonManager.String.IsInteger( hd ) )
			{
				CommonManager.Web.RegJs( this, "alert('温馨提示：\\n\\n[划帐人ID]输入值必须为数字！');location.href='TransSeach.aspx';", false );
				return;
			}
			if( zd != "" && !CommonManager.String.IsInteger( zd ) )
			{
				CommonManager.Web.RegJs( this, "alert('温馨提示：\\n\\n[接收人ID]输入值必须为数字！');location.href='TransSeach.aspx';", false );
				return;
			}
			//Response.End();

			//if (rr.ToString() != "0") searchtop = rr;
			if( zz.ToString() != "" )
			{
				SqlW = SqlW + " and UserName='" + zz + "'";
				para += "&u=" + zz;
			}

			if( jj.ToString() != "" )
			{
				SqlW = SqlW + " and UserNameZZ='" + jj + "'";
				para += "&uz=" + jj;
			}

			if( hd.ToString()!="")
			{
				SqlW = SqlW + " and UserID='" + hd + "'";
				para += "&uz=" + hd;
			}

			if( zd.ToString() != "" )
			{
				SqlW = SqlW + " and DestUserID='" + zd + "'";
				para += "&uz=" + zd;
			}

			/*if( ii.ToString() != "" )
			{
				SqlW = SqlW + " and IP='" + ii + "'";
				para += "&ip=" + ii;
			}*/
			if( t1.ToString() == "0" && t2.ToString() == "0" )
			{
				SqlW = SqlW + "";
			}
			else
			{
				SqlW = SqlW + " and (datediff(hour,TransTime,getdate())>=" + t1 + " and datediff(hour,TransTime,getdate())<=" + t2 + ")";
				para += "&t1=" + t1 + "&t2=" + t2;

			}

			if( mr.ToString() == "1" )
			{
				SqlW = SqlW + " and Money>=" + mm + "";
				para += "&m=" + mm;
			}
			else
			{
				SqlW = SqlW + " and Money<=" + mm + "";
				para += "&m=" + mm;
			}
			if( sr.ToString() == "1" )
			{
				SqlW = SqlW + " and Tax>=" + ss + "";
				para += "&t=" + ss;
			}
			else
			{
				SqlW = SqlW + " and Tax<=" + ss + "";
				para += "&t=" + ss;
			}
			//添加一个始终为真的条件来连接SQL
			SqlW = " and ID<>0 " + SqlW;
			//Response.Write(SqlW);
			titlenames = "转帐搜索记录列表";
		}
		else
		{
			//times = Limit.editCharacter(Limit.getFormValue("time"));
			times = times = Request.QueryString["time"];
			if( times == null || times.ToString() == "" )
			{
				SqlW = "";
				para = "";
				titlenames = "玩家转账记录列表";
			}
			else if( times != null && times.ToString() == "24" )
			{
				SqlW = " and datediff(hour,TransTime,getdate())<=" + times + "";
				para = "time=" + times + "";
				titlenames = "24小时玩家转账记录列表";
			}
			else
			{
				Alert( "温馨提示：\\n\\n参数传递错误！", null );
				return;
			}
		}

		DataSet ds = DbSession.Default.FromProc( "Web_pGetDataPager" )
			.AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
			.AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
			.AddInputParameter( "@Columns", DbType.String, "*" )
			.AddInputParameter( "@TableName", DbType.String, "Web_TransLog" )
			.AddInputParameter( "@Wheres", DbType.String, SqlW )
			.AddInputParameter( "@KeyName", DbType.String, "ID" )
			.AddInputParameter( "@OrderBy", DbType.String, "ID desc" )
			.ToDataSet();
		if( ds.Tables.Count > 0 && ds.Tables[1].Rows.Count > 0 )
		{
			anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
			anpPageIndex.CurrentPageIndex = PageIndex;

			TransList.DataSource = ds.Tables[1];
			TransList.DataBind();
			TransList.Visible = true;
			NoTransList.Visible = false;
		}
		else
		{
			this.NoTransList.Visible = true;
			TransList.Visible = false;
		}		
	}
}
