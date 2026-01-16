# CLAUDE.md - AI Assistant Guide for 7v7 Repository

> **Purpose**: This document provides AI assistants with comprehensive context about the codebase structure, development workflows, and conventions to follow when working on this project.

**Last Updated**: 2026-01-16
**Repository**: GenesisXUnknown/7v7
**Status**: Initial repository setup

---

## Table of Contents

1. [Project Overview](#project-overview)
2. [Codebase Structure](#codebase-structure)
3. [Development Workflows](#development-workflows)
4. [Git Conventions](#git-conventions)
5. [Code Conventions](#code-conventions)
6. [Testing Strategy](#testing-strategy)
7. [Key Technical Decisions](#key-technical-decisions)
8. [Common Tasks](#common-tasks)
9. [AI Assistant Guidelines](#ai-assistant-guidelines)
10. [Troubleshooting](#troubleshooting)

---

## Project Overview

### About This Project

**Status**: 🚧 Project initialization phase
**Type**: [To be determined based on first commits]

### Tech Stack

- **Languages**: [To be documented]
- **Frameworks**: [To be documented]
- **Build Tools**: [To be documented]
- **Package Manager**: [To be documented]
- **Runtime**: [To be documented]

### Repository Information

- **Main Branch**: [To be determined]
- **Remote**: `http://local_proxy@127.0.0.1:40412/git/GenesisXUnknown/7v7`
- **Current Branch**: `claude/claude-md-mkgco4vlp30tanfv-SOxNt`

---

## Codebase Structure

### Directory Layout

```
/home/user/7v7/
├── [Project structure to be documented as development proceeds]
└── .git/                    # Git metadata
```

### Key Directories

**To be documented** as the project structure is established. Typical structure might include:

- `/src` or `/lib` - Source code
- `/tests` or `/test` - Test files
- `/docs` - Documentation
- `/config` - Configuration files
- `/scripts` - Build and utility scripts
- `/public` or `/assets` - Static assets (if applicable)

### Important Files

**Configuration Files** (to be added):
- Build configuration
- Package/dependency management
- Linting and formatting rules
- Environment variables template
- CI/CD configuration

**Documentation Files** (to be added):
- README.md - Project introduction and setup
- CONTRIBUTING.md - Contribution guidelines
- CHANGELOG.md - Version history
- This CLAUDE.md file

---

## Development Workflows

### Initial Setup

```bash
# Clone the repository
git clone http://local_proxy@127.0.0.1:40412/git/GenesisXUnknown/7v7
cd 7v7

# [Additional setup steps to be documented]
```

### Build Process

**To be documented** based on the chosen tech stack.

Example patterns:
```bash
# Install dependencies
[package-manager] install

# Development build
[build-command] dev

# Production build
[build-command] build

# Run locally
[run-command] start
```

### Testing Workflow

**To be documented** as testing infrastructure is added.

```bash
# Run all tests
[test-command]

# Run specific test suite
[test-command] [suite]

# Run with coverage
[test-command] --coverage
```

### Code Quality

**Linting**:
- [To be documented - linter configuration]

**Formatting**:
- [To be documented - formatter configuration]

**Type Checking** (if applicable):
- [To be documented]

---

## Git Conventions

### Branch Naming

**AI Assistant Branches**:
- Format: `claude/claude-md-<session-id>-<unique-suffix>`
- Example: `claude/claude-md-mkgco4vlp30tanfv-SOxNt`
- **CRITICAL**: All AI assistant branches MUST start with `claude/` and end with matching session ID

**Feature Branches** (human developers):
- Format: `feature/<descriptive-name>`
- Example: `feature/user-authentication`

**Bug Fix Branches**:
- Format: `fix/<issue-description>`
- Example: `fix/login-validation-error`

### Commit Message Format

Follow conventional commit format:

```
<type>(<scope>): <subject>

<body>

<footer>
```

**Types**:
- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation changes
- `style`: Code style changes (formatting, missing semi-colons, etc.)
- `refactor`: Code refactoring
- `test`: Adding or updating tests
- `chore`: Maintenance tasks

**Examples**:
```
feat(auth): add JWT token authentication

Implemented JWT-based authentication with refresh tokens.
Added middleware for protected routes.

Closes #123
```

```
fix(api): resolve race condition in data fetching

Updated the data fetching logic to use proper async/await
patterns and prevent race conditions.
```

### Push Guidelines

**For AI Assistants**:
```bash
# Always use -u flag on first push
git push -u origin <branch-name>

# Branch must match pattern: claude/*-<session-id>
# Example:
git push -u origin claude/claude-md-mkgco4vlp30tanfv-SOxNt
```

**Retry Logic for Network Failures**:
- Retry up to 4 times with exponential backoff: 2s, 4s, 8s, 16s
- Only retry on network errors, not authentication or validation errors

**For Specific Branch Operations**:
```bash
# Fetch specific branch
git fetch origin <branch-name>

# Pull from specific branch
git pull origin <branch-name>
```

### Pull Request Process

1. **Create PR from feature branch to main**
2. **PR Title Format**: Clear, descriptive summary
3. **PR Description Should Include**:
   - Summary of changes (1-3 bullet points)
   - Test plan (checklist of verification steps)
   - Related issues/tickets

**Example PR Creation**:
```bash
gh pr create --title "Add user authentication system" --body "$(cat <<'EOF'
## Summary
- Implemented JWT-based authentication
- Added login/logout endpoints
- Created protected route middleware

## Test plan
- [ ] Verify login with valid credentials
- [ ] Verify login fails with invalid credentials
- [ ] Verify protected routes require authentication
- [ ] Verify token refresh mechanism
EOF
)"
```

---

## Code Conventions

### General Principles

1. **Keep it Simple**: Avoid over-engineering
2. **YAGNI**: You Aren't Gonna Need It - don't add features speculatively
3. **DRY with Caution**: Don't abstract too early; 3 instances before abstracting
4. **Explicit over Implicit**: Code should be self-documenting
5. **Security First**: Always validate at system boundaries

### Code Style

**To be documented** based on chosen language/framework.

Key areas to define:
- Naming conventions (variables, functions, classes)
- File naming patterns
- Code organization within files
- Comment style and when to use comments
- Error handling patterns
- Async/await patterns (if applicable)

### Security Guidelines

**For AI Assistants - Always Check For**:
- ❌ Command injection vulnerabilities
- ❌ XSS (Cross-Site Scripting)
- ❌ SQL injection
- ❌ Path traversal
- ❌ Exposed secrets or credentials
- ❌ Insecure authentication/authorization
- ✅ Input validation at system boundaries
- ✅ Proper error handling without information leakage
- ✅ Secure credential management

**Never Commit**:
- `.env` files with actual secrets
- `credentials.json` or similar files
- API keys or tokens
- Private keys or certificates
- Passwords or connection strings

---

## Testing Strategy

### Test Organization

**To be documented** as tests are added.

Typical structure:
```
tests/
├── unit/           # Unit tests
├── integration/    # Integration tests
├── e2e/           # End-to-end tests
└── fixtures/      # Test data and fixtures
```

### Testing Principles

1. **Test Behavior, Not Implementation**
2. **One Assertion Per Test** (where reasonable)
3. **Descriptive Test Names**: Should explain what is being tested
4. **Arrange-Act-Assert Pattern**
5. **Test Edge Cases**: Empty inputs, null values, boundary conditions

### Coverage Goals

**To be determined** based on project requirements.

---

## Key Technical Decisions

### Architecture Decisions

**To be documented** as architectural choices are made.

Format for recording decisions:
```markdown
#### Decision: [Title]
**Date**: YYYY-MM-DD
**Context**: Why this decision was needed
**Decision**: What was decided
**Alternatives Considered**: Other options
**Consequences**: Impact of this decision
```

### Dependencies

**Philosophy** (to be refined):
- Prefer established, well-maintained libraries
- Minimize dependency count
- Regularly audit for security vulnerabilities
- Document why each major dependency was chosen

---

## Common Tasks

### For AI Assistants Working on This Repository

#### Adding a New Feature

1. **Read existing code first** - Never propose changes without reading
2. **Use TodoWrite** to plan multi-step features
3. **Ask questions** using AskUserQuestion when unclear
4. **Keep scope minimal** - Only what was requested
5. **Check security** - Review for OWASP top 10 vulnerabilities
6. **Test your changes** - Run existing tests, add new tests if needed
7. **Commit with clear message** following conventions above
8. **Push to your claude/* branch**

#### Fixing a Bug

1. **Reproduce the issue** - Understand the bug first
2. **Read related code** - Context is critical
3. **Fix minimally** - Don't refactor surrounding code
4. **Verify the fix** - Test that it actually resolves the issue
5. **Check for regressions** - Ensure nothing else broke
6. **Commit the fix** with clear description of what was wrong

#### Refactoring

**Only refactor when explicitly requested** - Don't refactor as part of other tasks.

When refactoring:
1. Ensure tests exist and pass first
2. Make small, incremental changes
3. Run tests after each change
4. Don't change behavior, only structure
5. Commit each logical refactoring step

#### Creating Documentation

**Don't create documentation proactively** unless requested.

When creating docs:
- Focus on "why" not "what" (code shows what)
- Include examples
- Keep it up-to-date with code changes
- Use clear, concise language

---

## AI Assistant Guidelines

### Core Principles for AI Assistants

1. **Read Before Writing**
   - ALWAYS read files before editing them
   - Understand context before making changes
   - Never guess at code structure

2. **Plan Complex Tasks**
   - Use TodoWrite for multi-step tasks
   - Break down large features into manageable pieces
   - Update todos as you progress
   - Mark tasks complete immediately when done

3. **Communicate Clearly**
   - Ask questions when uncertain
   - Explain your reasoning
   - Don't use emojis unless requested
   - Be concise but complete

4. **Respect Scope**
   - Do only what was requested
   - Don't add "improvements" unless asked
   - Avoid over-engineering
   - No speculative features

5. **Security First**
   - Always validate inputs at boundaries
   - Check for common vulnerabilities
   - Never commit secrets
   - Fix security issues immediately

6. **Test Thoroughly**
   - Run tests after changes
   - Add tests for new functionality
   - Verify edge cases
   - Check for regressions

### Git Workflow for AI Assistants

**CRITICAL REQUIREMENTS**:

✅ **DO**:
- Develop on your assigned `claude/*` branch
- Commit with clear, descriptive messages
- Push to your branch when complete
- Use `git push -u origin <branch-name>` for first push
- Follow branch naming: `claude/*-<session-id>`
- Run git operations from the repository root

❌ **DO NOT**:
- Push to main or other branches without permission
- Use `--force` flags without explicit user request
- Skip hooks with `--no-verify`
- Amend commits that have been pushed
- Use `git commit --amend` unless explicitly meeting all conditions

**Retry Logic**:
- Network failures: Retry up to 4 times (2s, 4s, 8s, 16s delays)
- Authentication errors: Do not retry, report to user
- Validation errors: Do not retry, fix and try again

### Tool Usage Best Practices

**Prefer Specialized Tools**:
- Use `Read` instead of `cat`
- Use `Edit` instead of `sed/awk`
- Use `Write` instead of `echo >>`
- Use `Grep` instead of command-line `grep`
- Use `Glob` instead of `find`

**Parallel Execution**:
- Run independent commands in parallel
- Use single message with multiple tool calls
- Chain dependent commands with `&&`

**File Operations**:
- Always use absolute paths
- Check parent directories exist before creating files
- Quote paths with spaces

### When to Use Different Agents

- **Explore Agent**: Codebase exploration, understanding structure
- **Plan Agent**: Designing implementation strategies
- **General Purpose**: Multi-step research and search tasks
- **Bash**: Git operations, system commands (not file operations)

---

## Troubleshooting

### Common Issues

#### Git Push Fails with 403

**Cause**: Branch name doesn't match required pattern
**Solution**: Ensure branch starts with `claude/` and ends with session ID

```bash
# Check current branch
git branch --show-current

# If incorrect, create correct branch
git checkout -b claude/claude-md-<session-id>-<suffix>
```

#### Network Errors on Git Operations

**Cause**: Temporary network issues
**Solution**: Retry with exponential backoff (automatically handled)

#### Tests Failing After Changes

**Cause**: Code changes broke existing functionality
**Solution**:
1. Review test output carefully
2. Understand what the test expects
3. Fix code to meet test requirements
4. Don't mark tasks as complete until tests pass

#### Merge Conflicts

**Cause**: Concurrent changes to same files
**Solution**:
1. Fetch latest from main: `git fetch origin main`
2. Merge or rebase as appropriate
3. Resolve conflicts manually
4. Test after resolution
5. Commit merge resolution

---

## Keeping This Document Updated

### When to Update CLAUDE.md

This document should be updated when:

- ✅ Project structure changes significantly
- ✅ New development tools are adopted
- ✅ Conventions or workflows are established
- ✅ New architectural decisions are made
- ✅ Testing strategy evolves
- ✅ New common tasks or patterns emerge

### Update Process

1. Read current CLAUDE.md
2. Make targeted updates to relevant sections
3. Update "Last Updated" date
4. Commit with message: `docs: update CLAUDE.md with [specific changes]`
5. Keep information current and accurate

### Versioning

Track major updates:
- **v1.0** (2026-01-16): Initial template created
- [Future versions to be added]

---

## Additional Resources

### External Documentation

**To be added** as project develops:
- Project website or wiki
- API documentation
- Design documents
- Architecture diagrams

### Getting Help

**For AI Assistants**:
- Read this document thoroughly before starting work
- Use the Task/Explore agents to understand unfamiliar parts of codebase
- Ask user questions when genuinely unclear
- Check existing patterns in codebase before creating new ones

**For Human Developers**:
- [To be documented - team contacts, channels, etc.]

---

## Appendix

### Glossary

**To be expanded** as project-specific terminology develops.

### File Reference

Quick reference to important files:
- `CLAUDE.md` - This file - AI assistant guide
- [Additional files to be documented]

---

**Note to AI Assistants**: This document is your primary reference for working on this codebase. Always consult it before making significant decisions. When in doubt, ask the user for clarification rather than making assumptions. Keep this document updated as you learn more about the project conventions and structure.
