/* -*- Mode: Java; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: NPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Mozilla Communicator client code.
 *
 * The Initial Developer of the Original Code is 
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 * Alec Flett <alecf@netscape.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or 
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the NPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the NPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

var elements = [];
var numItems;
var list;
var param;

function selectDialogOnLoad() {
  param = window.arguments[0].QueryInterface( Components.interfaces.nsIDialogParamBlock  );
  if( !param )
  dump( " error getting param block interface\n" );

  var messageText = param.GetString( 1 );
  {
    var messageFragment;

    // Let the caller use "\n" to cause breaks
    // Translate these into <br> tags
    var messageParent = (document.getElementById("info.txt"));
    var done = false;
    while (!done) {
      var breakIndex = messageText.indexOf('\n');
      if (breakIndex == 0) {
        // Ignore break at the first character
        messageText = messageText.slice(1);
        messageFragment = "";
      } else if (breakIndex > 0) {
        // The fragment up to the break
        messageFragment = messageText.slice(0, breakIndex);

        // Chop off fragment we just found from remaining string
        messageText = messageText.slice(breakIndex+1);
      } else {
        // "\n" not found. We're done
        done = true;
        messageFragment = messageText;
      }
      messageParent.setAttribute("value", messageFragment);
    }
  }

  var windowTitle = param.GetString( 0 );
  window.title = windowTitle;

  list = document.getElementById("list");
  numItems = param.GetInt( 2 )

  var i;
  for ( i = 2; i <= numItems+1; i++ ) {
    var newString = param.GetString( i );
    if (newString == "") {
      newString = "<>";
    }
    elements[i-2] = AppendStringToTreelist(list, newString);
  }
  list.selectItem(elements[0]);
  list.focus();

  // resize the window to the content
  window.sizeToContent();

  // Move to the right location
  moveToAlertPosition();
  param.SetInt(0, 1 );
  centerWindowOnScreen();
}

function commonDialogOnOK() {
  for (var i=0; i<numItems; i++) {
    if (elements[i] == list.selectedItems[0]) {
      param.SetInt(2, i );
      break;
    }
  }
  param.SetInt(0, 0 );
  return true;
}

function commonDialogOnCancel() {
  for (var i=0; i<numItems; i++) {
    if (elements[i]) {
      param.SetInt(2, i );
      break;
    }
  }
  param.SetInt(0, 1 );
  return true;
}

// following routine should really be in a global utilities package

function AppendStringToTreelist(tree, string)
{
  if (tree)
  {
    var treechildren = document.getElementById('child');

    var treeitem = document.createElementNS("http://www.mozilla.org/keymaster/gatekeeper/there.is.only.xul", "treeitem");
    var treerow = document.createElementNS("http://www.mozilla.org/keymaster/gatekeeper/there.is.only.xul", "treerow");
    var treecell = document.createElementNS("http://www.mozilla.org/keymaster/gatekeeper/there.is.only.xul", "treecell");
    if (treeitem && treerow && treecell)
    {
      treecell.setAttribute("label", string);
      treerow.appendChild(treecell);
      treeitem.appendChild(treerow);
      treechildren.appendChild(treeitem)
      var len = Number(tree.getAttribute("length"));
      if (!len) len = -1;
      tree.setAttribute("length",len+1);
      return treeitem;
    }
  }
  return null;
}
