/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.0 (the "License"); you may not use this file except in
 * compliance with the License.  You may obtain a copy of the License at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See
 * the License for the specific language governing rights and limitations
 * under the License.
 *
 * The Original Code is Mozilla Communicator client code.
 *
 * The Initial Developer of the Original Code is Netscape Communications
 * Corporation.  Portions created by Netscape are Copyright (C) 1998
 * Netscape Communications Corporation.  All Rights Reserved.
 */
#ifndef nsWebCrawler_h___
#define nsWebCrawler_h___

#include "nsIBrowserWindow.h"
#include "nsIDocumentLoaderObserver.h"
#include "nsVoidArray.h"
#include "nsString.h"

class nsIAtom;
class nsIContent;
class nsIDocument;
class nsITimer;
class nsIURI;
class nsIPresShell;
class nsViewerApp;
class AtomHashTable;

class nsWebCrawler : public nsIDocumentLoaderObserver {
public:
  // Make a new web-crawler for the given viewer. Note: the web
  // crawler does not addref the viewer.
  nsWebCrawler(nsViewerApp* aViewer);

  // nsISupports
  NS_DECL_ISUPPORTS

  // nsIDocumentLoaderObserver
#ifdef NECKO
	NS_IMETHOD OnStartDocumentLoad(nsIDocumentLoader* loader, nsIURI* aURL, const char* aCommand);
	NS_IMETHOD OnEndDocumentLoad(nsIDocumentLoader* loader, nsIChannel* channel, nsresult aStatus, nsIDocumentLoaderObserver* aObserver);
	NS_IMETHOD OnStartURLLoad(nsIDocumentLoader* loader, nsIChannel* channel, nsIContentViewer* aViewer);
	NS_IMETHOD OnProgressURLLoad(nsIDocumentLoader* loader, nsIChannel* channel, PRUint32 aProgress, PRUint32 aProgressMax);
	NS_IMETHOD OnStatusURLLoad(nsIDocumentLoader* loader, nsIChannel* channel, nsString& aMsg);
	NS_IMETHOD OnEndURLLoad(nsIDocumentLoader* loader, nsIChannel* channel, nsresult aStatus);
	NS_IMETHOD HandleUnknownContentType(nsIDocumentLoader* loader, nsIChannel* channel, const char *aContentType,const char *aCommand );		
#else
  NS_IMETHOD OnStartDocumentLoad(nsIDocumentLoader* loader, nsIURI* aURL,
                                 const char* aCommand);
  NS_IMETHOD OnEndDocumentLoad(nsIDocumentLoader* loader, nsIURI *aURL,
                               PRInt32 aStatus, 
                               nsIDocumentLoaderObserver * aObserver);
  NS_IMETHOD OnStartURLLoad(nsIDocumentLoader* loader, nsIURI* aURL,
                            const char* aContentType, 
                            nsIContentViewer* aViewer);
  NS_IMETHOD OnProgressURLLoad(nsIDocumentLoader* loader,
                               nsIURI* aURL, PRUint32 aProgress, 
                               PRUint32 aProgressMax);
  NS_IMETHOD OnStatusURLLoad(nsIDocumentLoader* loader, nsIURI* aURL,
                             nsString& aMsg);
  NS_IMETHOD OnEndURLLoad(nsIDocumentLoader* loader, nsIURI* aURL,
                          PRInt32 aStatus);
  NS_IMETHOD HandleUnknownContentType(nsIDocumentLoader* loader,
                                      nsIURI *aURL,
                                      const char *aContentType,
                                      const char *aCommand);
#endif

  // Add a url to load
  void AddURL(const nsString& aURL);

  // Add a domain that is safe to load url's from
  void AddSafeDomain(const nsString& aDomain);

  // Add a domain that must be avoided
  void AddAvoidDomain(const nsString& aDomain);

  void SetBrowserWindow(nsIBrowserWindow* aWindow);
  void GetBrowserWindow(nsIBrowserWindow** aWindow);

  // Set the delay (by default, the timer is set to one second)
  void SetDelay(PRInt32 aSeconds) {
    mDelay = aSeconds;
  }

  void EnableJiggleLayout() {
    mJiggleLayout = PR_TRUE;
  }

  // If set to TRUE the loader will post an exit message on exit
  void SetExitOnDone(PRBool aPostExit) {
    mPostExit = aPostExit;
  }

  // Start loading documents
  void Start();

  // Enable the crawler; when a document contains links to other
  // documents the crawler will go to them subject to the limitations
  // on the total crawl count and the domain name checks.
  void EnableCrawler();

  void SetRecordFile(FILE* aFile) {
    mRecord = aFile;
  }

  void SetMaxPages(PRInt32 aMax) {
    mMaxPages = aMax;
  }

  void SetOutputDir(const nsString& aOutputDir);

  void SetRegressionDir(const nsString& aOutputDir);

  void SetEnableRegression(PRBool aSetting) {
    mRegressing = aSetting;
  }

  void LoadNextURL();

  void SetVerbose(PRBool aSetting) {
    mVerbose = aSetting;
  }

protected:
  virtual ~nsWebCrawler();

  void FindURLsIn(nsIDocument* aDocument, nsIContent* aNode);

  void FindMoreURLs();

  PRBool OkToLoad(const nsString& aURLSpec);

  void RecordLoadedURL(const nsString& aURLSpec);

  /** generate an output name from a URL */
  FILE* GetOutputFile(nsIURI *aURL, nsString& aOutputName);

  nsIPresShell* GetPresShell();

  void PerformRegressionTest(const nsString& aOutputName);

  nsIBrowserWindow* mBrowser;
  nsViewerApp* mViewer;
  nsITimer* mTimer;
  FILE* mRecord;
  nsIAtom* mLinkTag;
  nsIAtom* mFrameTag;
  nsIAtom* mIFrameTag;
  nsIAtom* mHrefAttr;
  nsIAtom* mSrcAttr;
  nsIAtom* mBaseHrefAttr;
  AtomHashTable* mVisited;
  nsString mOutputDir;

  PRBool mCrawl;
  PRBool mJiggleLayout;
  PRBool mPostExit;
  PRInt32 mDelay;
  PRInt32 mMaxPages;

  nsString mCurrentURL;
  PRBool mVerbose;
  PRBool mRegressing;
  nsString mRegressionDir;

  nsVoidArray mPendingURLs;
  nsVoidArray mSafeDomains;
  nsVoidArray mAvoidDomains;
};

#endif /* nsWebCrawler_h___ */
