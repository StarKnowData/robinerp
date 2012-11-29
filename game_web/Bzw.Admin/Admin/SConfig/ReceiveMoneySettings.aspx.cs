using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using Bzw.Data;
using BCST.Common;
 

    public partial class Admin_SConfig_ReceiveMoneySettings :AdminBasePage
    {
        public int rowid = 0;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                AdminPopedom.IsHoldModel("09");
                if (Request.QueryString["act"] != null && Request.QueryString["act"] == "del")
                {
                    DelReceiveMoney();
                }
                BindRecord();
            }
        }
        public void BindRecord()
        {
            DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")    //执行分页的存储过程
              .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)  //当前页码显示的数据
              .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)  //页码的索引
              .AddInputParameter("@Columns", DbType.String, "*")          //需要获取哪些列
              .AddInputParameter("@TableName", DbType.String, "TReceiveMoneyDefind")  //表或视图的名称
              .AddInputParameter("@Wheres", DbType.String, "")  //查询条件
              .AddInputParameter("@KeyName", DbType.String, "id")     //设置主键的名称
              .AddInputParameter("@OrderBy", DbType.String, "id asc")  //设置排序的字段
              .ToDataSet();                                        //执行数据查询语句

            if (ds.Tables.Count > 0)
            {

                anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0]; //获取总的记录条数
                anpPageIndex.CurrentPageIndex = PageIndex;   //  获取页码的索引
                if (ds.Tables[1].Rows.Count > 0)
                {
                    rptDataList.DataSource = ds.Tables[1];  //获取数据表中的数据
                    rptDataList.DataBind();       //将数据绑定到分页空间上
                    rptDataList.Visible = true;  //设置分页控件可不可用
                    ltNonData.Visible = false;  //设置要不要显示 “无记录语句”
                }
                else
                {
                    rptDataList.Visible = false;
                    ltNonData.Visible = true;
                }
            }
        }
        public void DelReceiveMoney()
        {
            int id = Convert.ToInt32(Request.QueryString["id"].ToString());
            if (id > 0)
            {
                int SqlState = DbSession.Default.FromSql("delete from TreceiveMoneyDefind where id=@id  update TreceiveMoneyDefind set id=id-1 where id>@id").AddInputParameter("@id",DbType.Int32,id).Execute();
                if (SqlState > 0)
                    CommonManager.Web.RegJs(this, "alert('温馨提示：\\n\\n删除成功！');location.href='ReceiveMoneySettings.aspx'", true);
                else
                    CommonManager.Web.RegJs(this, "alert('温馨提示：\\n\\n删除失败！！');", true);
            }
        }

    }
 
