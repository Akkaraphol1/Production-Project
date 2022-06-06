//16jM-XZbA4_WF0UQpt1QGi-Tck-TP3kFaDf-KOB62R18

function doGet(e) { 
  Logger.log( JSON.stringify(e) );
  var result = 'Ok';
  if (e.parameter == 'undefined') {
    result = 'No Parameters';
  }
  else {
    var sheet_id = '16jM-XZbA4_WF0UQpt1QGi-Tck-TP3kFaDf-KOB62R18'; 	// Spreadsheet ID
    var sheet = SpreadsheetApp.openById(sheet_id).getActiveSheet();
    var newRow = sheet.getLastRow() + 1;						
    var rowData = [];
    var Curr_Date = new Date();
     var Curr_Date2 = Utilities.formatDate(Curr_Date, "Asia/Bangkok", 'yyyy-MM-dd');
    rowData[1] = Curr_Date2; // Time in column B

    var Curr_Time = Utilities.formatDate(Curr_Date, "Asia/Bangkok", 'HH:mm:ss');
    rowData[2] = Curr_Time; // Time in column C
    for (var param in e.parameter) {
      Logger.log('In for loop, param=' + param);
      var value = stripQuotes(e.parameter[param]);
      Logger.log(param + ':' + e.parameter[param]);
      switch (param) {
        case 'id':
          rowData[0] = value; // id in column A
          result = 'id Written on column A'; 
          break;
        case 'status':
          rowData[2] = value; // status in column C
          result = 'status Written on column C'; 
          break;
      }
    }
    Logger.log(JSON.stringify(rowData));
    var newRange = sheet.getRange(newRow, 1, 1, rowData.length);
    newRange.setValues([rowData]);
  }
  return ContentService.createTextOutput(result);
}
function stripQuotes( value ) {
  return value.replace(/^["']|['"]$/g, "");
}


