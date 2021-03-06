
var adddialog = new mdui.Dialog('#add-dialog');
var deletedialog = new mdui.Dialog('#delete-dialog');
var modifydialog = new mdui.Dialog('#modify-dialog');
var scoredialog = new mdui.Dialog('#score-dialog');
var listdeletedialog = new mdui.Dialog("#list-delete");
var delsno, delname;
var modifyid,listdelid;
document.getElementById('add').addEventListener('click', function () {
    adddialog.open();
});
document.getElementById('delete').addEventListener('click', function () {
    deletedialog.open();

});
function listdelete(id) {
    listdelid=id;
    $.post("./modules/getCourseByNo.php",
            {
                Cno: id,
            },
            function (data, status) {
                if (data.data.length != 0) {
                    var listname=data.data[1];
                    var listno=data.data[0];
                    $("#list-delete-note").text("确认删除课程"+listname+"("+listno+")?");
                    listdeletedialog.open();
                }
            }
    );
}
function modify(id) {
    modifyid=id;
    $.post("./modules/getCourseByNo.php",
            {
                Cno: id,
            },
            function (data, status) {
                if (data.data.length != 0) {
                    $("#modify-cname").val(data.data[1]);
                    $("#modify-teacher").val(data.data[2]);
                    $("#modify-credit").val(data.data[3]);
                    modifydialog.open();
                }
            }
    );
}
function score(id) {
    $.post("./modules/getAllScore.php",
        {
            Cno: id,
        },
        function (data, status) {
            var you=0;
      var liang=0;
      var zhong=0;
      var all=0;
            if (data.code == 200 && data.data.content.length > 0) {
                    $("#chips").empty();
                    $("#score_context").empty();
                    $("#score_name").text(data.data.course.Cname);
                    $("#score_cno").text(data.data.course.Cno);
                                       var $sTemp = $("#score_context");
                    for (var i = 0; i < data.data.content.length; i++) {
                      all=all+1;
                        if(data.data.content[i].Score<60){
                            $sTemp.append("<div><span class=\"score-tit\">"+data.data.content[i].Sname+"：</span><span style=\"color:#f44336;\" class=\"score-inf\">"+data.data.content[i].Score+"</span></div>");
                        }else if(data.data.content[i].Score>=60&&(data.data.content[i].Score<75)){
                          zhong=zhong+1;
                            $sTemp.append("<div><span class=\"score-tit\">"+data.data.content[i].Sname+"：</span><span style=\"color:#fff176;\" class=\"score-inf\">"+data.data.content[i].Score+"</span></div>");
                        }else if(data.data.content[i].Score>=75&&(data.data.content[i].Score<85)){
                          liang=liang+1;
                            $sTemp.append("<div><span class=\"score-tit\">"+data.data.content[i].Sname+"：</span><span style=\"color:#cddc39;\" class=\"score-inf\">"+data.data.content[i].Score+"</span></div>");
                        }else{
                          you=you+1;
                            $sTemp.append("<div><span class=\"score-tit\">"+data.data.content[i].Sname+"：</span><span style=\"color:#4caf50;\" class=\"score-inf\">"+data.data.content[i].Score+"</span></div>");
                        }
                    }
                    //$sTemp.appendTo("#score_context");
               var $trTemp = $("<div></div>");
                    $trTemp.append("<div class=\"mdui-chip\"><span class=\"mdui-chip-title\">最高分："+data.data.basic.highest_C+" "+data.data.basic.highest_S+"</span></div>");
                    $trTemp.append("<div class=\"mdui-chip\"><span class=\"mdui-chip-title\">最低分："+data.data.basic.lowest_C+" "+data.data.basic.lowest_S+"</span></div>");
                    $trTemp.append("<div class=\"mdui-chip\"><span class=\"mdui-chip-title\">平均分："+data.data.basic.ave+"</span></div>");
                    $trTemp.append("<div class=\"mdui-chip\"><span class=\"mdui-chip-title\">及格/不及格："+(you+liang+zhong)+"("+((you+liang+zhong)/all*100).toFixed(2)+"%)/"+(all-you-liang-zhong)+"("+((all-you-liang-zhong)/all*100).toFixed(2)+"%)</span></div>");
              		$trTemp.append("<div class=\"mdui-chip\"><span class=\"mdui-chip-title\">优/良/中："+you+"("+((you/all)*100).toFixed(2)+"%)"+"/"+liang+"("+((liang/all)*100).toFixed(2)+"%)"+"/"+zhong+"("+((zhong/all)*100).toFixed(2)+"%)"+"</span></div>");
                    $trTemp.appendTo("#chips");
                    mdui.mutation();
                    scoredialog.open();
            }
        }
    )
}

function flashdata() {
    $.post("./modules/searchCourse.php",
        {
            keywords: "",
        },
        function (data, status) {
            if (data.code == 200 && data.data.length > 0) {
                $("#table_data").empty();
                for (var i = 0; i < data.data.length; i++) {                //动态创建一个tr行标签,并且转换成jQuery对象
                    var $trTemp = $("<tr></tr>");                //往行里面追加 td单元格
                    $trTemp.append("<td>" + data.data[i][0] + "</td>");
                    $trTemp.append("<td>" + data.data[i][1] + "</td>");
                    $trTemp.append("<td>" + data.data[i][2] + "</td>");
                    $trTemp.append("<td>" + data.data[i][3] + "</td>");
                    $trTemp.append("<td><button onclick=\"score('" + data.data[i][0] + "')\" class=\"mdui-btn mdui-btn-icon mdui-ripple table-btn\"><i class=\"mdui-icon material-icons\">remove_red_eye</i></button></td>");
                    $trTemp.append("<td><button onclick=\"modify('" + data.data[i][0] + "')\" class=\"mdui-btn mdui-btn-icon mdui-ripple\"><i class=\"mdui-icon material-icons table-btn\">mode_edit</i></button><button onclick=\"listdelete('" + data.data[i][0] + "')\" class=\"mdui-btn mdui-btn-icon mdui-ripple\"><i class=\"mdui-icon material-icons table-btn\">delete</i></button></td>");
                    $trTemp.appendTo("#table_data");
                    mdui.mutation();
                }
            } else {
                $("#table_data").empty();
                var $trTemp = $("<tr></tr>");                //往行里面追加 td单元格
                $trTemp.append("<td>无</td>");
                $trTemp.append("<td>无</td>");
                $trTemp.append("<td>无</td>");
                $trTemp.append("<td>无</td>");
                $trTemp.append("<td></td>");
                $trTemp.append("<td></td>");
                $trTemp.appendTo("#table_data");
                mdui.mutation();
            }
        }
    )
}
$(document).ready(function () {
    flashdata();
    $("#waiting").hide();
    $("#modify-conf").click(function () {
        $.post("./modules/updateCourse.php",
            {
                Cname: $("#modify-cname").val(),
                Cno: modifyid,
                Credit: $("#modify-credit").val(),
                Teacher: $("#modify-teacher").val(),
            },
            function (data, status) {
                alert(data.msg);
                $("#modify-cname").val("");
                $("#modify-credit").val("");
                $("#modify-teacher").val("");
                modifydialog.close();
                flashdata();
            }
        )
    });
    $("#addbtn").click(function () {
        $.post("./modules/addCourse.php",
            {
                Cname: $("#Cname").val(),
                Cno: $("#Cno").val(),
                Credit: $("#Credit").val(),
                Teacher: $("#Teacher").val(),
            },
            function (data, status) {
                alert(data.msg);
                $("#Cname").val("");
                $("#Cno").val("");
                $("#Credit").val("");
                $("#Teacher").val("");
                flashdata();
            }
        )
    });
    $("#del-querys").click(function () {
        $("#waiting").show();
        $.post("./modules/getCourseByNo.php",
            {
                Cno: $("#del-cno").val(),
            },
            function (data, status) {
                $("#waiting").hide();
                if (data.data.length != 0) {
                    $("#del-cnoo").html(data.data[0]);
                    $("#del-cname").html(data.data[1]);
                    $("#del-teacher").html(data.data[2]);
                    $("#del-credit").html(data.data[3]);
                    delsno = data.data[0];
                    delname = data.data[1];
                } else {
                    $("#del-snoo").html("无此课程");
                    $("#del-sname").html("无此课程");
                    $("#del-sclno").html("无此课程");
                    $("#del-ssex").html("无此课程");
                    delsno = "";
                    delname = "";
                }
            }
        )
    });
    $("#list-delete-cancel").click(function () {
        listdeletedialog.close();
        $("list-delete-note").text("");
    });
    $("#list-delete-conf").click(function () {
        $.post("./modules/deleteCourse.php",
            {
                Cno: listdelid,
            },
            function (data, status) {
                alert(data.msg);
                listdeletedialog.close();
                flashdata();
            }
        )
    });
    $("#del-query-conf").click(function () {
        $.post("./modules/deleteCourse.php",
            {
                Cno: delsno,
            },
            function (data, status) {
                $("#del-cno").val("");
                $("#del-cnoo").html("无此课程");
                $("#del-cname").html("无此课程");
                $("#del-teacher").html("无此课程");
                $("#del-credit").html("无此课程");
                delsno = "";
                delname = "";
                deletedialog.close();
                alert(data.msg);
                flashdata();
            }
        )
    });
    $("#search").bind("input propertychange", function (event) {
        $.post("./modules/searchCourse.php",
            {
                keywords: $("#search").val(),
            },
            function (data, status) {
                if (data.code == 200 && data.data.length > 0) {
                    $("#table_data").empty();
                    for (var i = 0; i < data.data.length; i++) {                //动态创建一个tr行标签,并且转换成jQuery对象
                        var $trTemp = $("<tr></tr>");                //往行里面追加 td单元格
                        $trTemp.append("<td>" + data.data[i][0] + "</td>");
                        $trTemp.append("<td>" + data.data[i][1] + "</td>");
                        $trTemp.append("<td>" + data.data[i][2] + "</td>");
                        $trTemp.append("<td>" + data.data[i][3] + "</td>");
                        $trTemp.append("<td><button onclick=\"score('" + data.data[i][0] + "')\" class=\"mdui-btn mdui-btn-icon mdui-ripple table-btn\"><i class=\"mdui-icon material-icons\">remove_red_eye</i></button></td>");
                        $trTemp.append("<td><button onclick=\"modify('" + data.data[i][0] + "')\" class=\"mdui-btn mdui-btn-icon mdui-ripple\"><i class=\"mdui-icon material-icons table-btn\">mode_edit</i></button><button onclick=\"listdelete('" + data.data[i][0] + "')\" class=\"mdui-btn mdui-btn-icon mdui-ripple\"><i class=\"mdui-icon material-icons table-btn\">delete</i></button></td>");
                        $trTemp.appendTo("#table_data");
                        mdui.mutation();
                    }
                } else {
                    $("#table_data").empty();
                    var $trTemp = $("<tr></tr>");                //往行里面追加 td单元格
                    $trTemp.append("<td>无</td>");
                    $trTemp.append("<td>无</td>");
                    $trTemp.append("<td>无</td>");
                    $trTemp.append("<td>无</td>");
                    $trTemp.append("<td></td>");
                    $trTemp.append("<td></td>");
                    $trTemp.appendTo("#table_data");
                    mdui.mutation();
                }
            }
        )
    });
});
