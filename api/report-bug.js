/**
 * Bug-report serverless function for the Akhenaten docs site.
 *
 * Receives a JSON POST from docs/reportbug.html and opens an issue on
 * dalerank/Akhenaten via the GitHub REST API.
 *
 * Spam protection is intentionally lightweight:
 *   - hidden honeypot field ("website") — must be empty
 *   - submission must arrive at least MIN_FORM_AGE_MS after page load
 *     (bots typically POST instantly)
 *
 * The handler is platform-agnostic: it takes a standard `Request` and
 * returns a `Response`. It runs unchanged on:
 *
 *   Cloudflare Workers
 *     wrangler.toml + this file's default export.
 *     Set secret: wrangler secret put GITHUB_TOKEN
 *     Set var:    ALLOWED_ORIGIN (e.g. https://dalerank.github.io)
 *
 *   Netlify Functions (under netlify/functions/report-bug.js)
 *     Import the named `handle` export and pass `process.env` as env.
 *
 *   Vercel Edge Functions (under api/report-bug.js)
 *     Add `export const config = { runtime: 'edge' };` and wrap `handle`.
 *
 * Required env vars:
 *   GITHUB_TOKEN   - fine-grained PAT with Issues: write on
 *                    dalerank/Akhenaten. Issues will be authored by
 *                    the token's owner.
 *   ALLOWED_ORIGIN - exact origin of the deployed docs site
 *                    (default: https://dalerank.github.io).
 */

const REPO = 'dalerank/Akhenaten';
const TITLE_MAX = 120;
const BODY_MIN = 20;
const BODY_MAX = 8000;
const NAME_MAX = 80;
const EMAIL_MAX = 200;
const MIN_FORM_AGE_MS = 3000;
const MAX_FORM_AGE_MS = 24 * 60 * 60 * 1000;

export default {
  fetch: (request, env, ctx) => handle(request, env),
};

export async function handle(request, env) {
  const e = env || (typeof process !== 'undefined' ? process.env : {}) || {};
  const allowedOrigin = e.ALLOWED_ORIGIN || 'https://dalerank.github.io';

  if (request.method === 'OPTIONS') {
    return new Response(null, { status: 204, headers: corsHeaders(allowedOrigin) });
  }

  if (request.method !== 'POST') {
    return json({ ok: false, error: 'Method not allowed.' }, 405, allowedOrigin);
  }

  let payload;
  try {
    payload = await request.json();
  } catch {
    return json({ ok: false, error: 'Invalid JSON body.' }, 400, allowedOrigin);
  }

  const title = stripControl((payload.title || '').toString()).trim();
  const body = (payload.body || '').toString();
  const name = stripControl((payload.name || '').toString()).trim();
  const email = stripControl((payload.email || '').toString()).trim();
  const honeypot = (payload.website || '').toString();
  const loadedAt = Number(payload.loadedAt);

  if (honeypot) {
    return json({ ok: false, error: 'Spam detected.' }, 400, allowedOrigin);
  }
  if (!Number.isFinite(loadedAt)) {
    return json({ ok: false, error: 'Spam detected.' }, 400, allowedOrigin);
  }
  const formAge = Date.now() - loadedAt;
  if (formAge < MIN_FORM_AGE_MS || formAge > MAX_FORM_AGE_MS) {
    return json({ ok: false, error: 'Spam detected.' }, 400, allowedOrigin);
  }
  if (!title || title.length > TITLE_MAX) {
    return json({ ok: false, error: 'Title is required (1-' + TITLE_MAX + ' chars).' }, 400, allowedOrigin);
  }
  if (body.trim().length < BODY_MIN || body.length > BODY_MAX) {
    return json(
      { ok: false, error: 'Description must be ' + BODY_MIN + '-' + BODY_MAX + ' characters.' },
      400,
      allowedOrigin
    );
  }
  if (name.length > NAME_MAX || email.length > EMAIL_MAX) {
    return json({ ok: false, error: 'Name or email too long.' }, 400, allowedOrigin);
  }

  const githubToken = e.GITHUB_TOKEN;
  if (!githubToken) {
    return json({ ok: false, error: 'Server is not configured.' }, 500, allowedOrigin);
  }

  const reporter = name || 'anonymous';
  const emailLine = email ? ' <' + email + '>' : '';
  const issueBody =
    body.trimEnd() +
    '\n\n---\n' +
    '*Submitted via the Akhenaten website bug-report form.*\n' +
    '*Reporter: ' + reporter + emailLine + '*\n';

  const ghResponse = await fetch('https://api.github.com/repos/' + REPO + '/issues', {
    method: 'POST',
    headers: {
      'Authorization': 'Bearer ' + githubToken,
      'Accept': 'application/vnd.github+json',
      'X-GitHub-Api-Version': '2022-11-28',
      'Content-Type': 'application/json',
      'User-Agent': 'akhenaten-bug-form',
    },
    body: JSON.stringify({
      title: title,
      body: issueBody,
      labels: ['bug', 'from-website'],
    }),
  });

  if (ghResponse.status !== 201) {
    return json(
      { ok: false, error: 'GitHub rejected the issue (status ' + ghResponse.status + ').' },
      502,
      allowedOrigin
    );
  }

  const issue = await ghResponse.json();
  return json({ ok: true, url: issue.html_url }, 201, allowedOrigin);
}

function stripControl(s) {
  return s.replace(/[\x00-\x08\x0B\x0C\x0E-\x1F\x7F]/g, '');
}

function corsHeaders(origin) {
  return {
    'Access-Control-Allow-Origin': origin,
    'Access-Control-Allow-Methods': 'POST, OPTIONS',
    'Access-Control-Allow-Headers': 'Content-Type',
    'Access-Control-Max-Age': '86400',
    'Vary': 'Origin',
  };
}

function json(payload, status, origin) {
  return new Response(JSON.stringify(payload), {
    status: status,
    headers: {
      'Content-Type': 'application/json; charset=utf-8',
      ...corsHeaders(origin),
    },
  });
}
