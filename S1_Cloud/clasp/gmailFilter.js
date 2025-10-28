/**
 * Creates a Gmail filter that archives emails from a specific sender.
 */
function createGmailFilter() {
  const filter = GmailApp.createFilter()
    .from('example@example.com')
    .archive();
  Logger.log('Created filter: ' + filter.getId());
}
