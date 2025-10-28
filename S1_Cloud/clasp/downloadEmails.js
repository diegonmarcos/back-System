/**
 * Downloads all emails from the last year and saves them to a file in Google Drive.
 */
function downloadEmails() {
  const query = 'newer_than:1y';
  const threads = GmailApp.search(query);
  let content = '';

  for (const thread of threads) {
    const messages = thread.getMessages();
    for (const message of messages) {
      content += 'From: ' + message.getFrom() + '\n';
      content += 'Subject: ' + message.getSubject() + '\n';
      content += 'Date: ' + message.getDate() + '\n';
      content += 'Body: \n' + message.getPlainBody() + '\n';
      content += '---------------------------------\n';
    }
  }

  DriveApp.createFile('emails.txt', content);
  Logger.log('Emails downloaded to emails.txt in your Google Drive.');
}
